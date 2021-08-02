#include QMK_KEYBOARD_H


#include "oled.h"
#include "config.h"

// forwards
bool is_keyboard_left(void);
const char *read_logo(void);
extern const unsigned char font[] PROGMEM;

#define ROW_1 OLED_DISPLAY_WIDTH
#define ROW_2 (OLED_DISPLAY_WIDTH * 2)

static uint32_t oled_sleep_timer = 0;

// 40 fps
#define FRAME_TIMEOUT (1000/40)
// 30 sec
#define SLEEP_TIMEOUT 120000

///////////////////////////////////////////////////////

// WPM-responsive animation stuff here
#define IDLE_FRAMES 5
#define IDLE_SPEED 20 // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#define TAP_FRAMES 7
#define TAP_SPEED 41// above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 512 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_tap_frame = 1;
uint8_t current_idle_frame = 2;

///////////////////////////////////////////////////////

static uint8_t next_bar_val = 0;
static uint8_t next_log_byte[OLED_FONT_WIDTH] = {0};

#define BAR_KEY_WEIGHT 128
#define BAR_KEY_DECAY_MAX 18
static uint8_t bar_key_decay = BAR_KEY_DECAY_MAX;

// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 0x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 1x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  20,  19,  27,  26,  22, ' ', ' ', ' ',  // 2x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 128,   7,   7,   7,   7,   7,   7,  // 3x
      7,   7,   7,   7,   7,   7, ' ', ' ', ' ', ' ', ' ',  30,  16,  31,  17,  27,  // 4x
     26,  25,  24, ' ', ' ', ' ', ' ', ' ', ' ',  20, ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   7,   7,   7,   7,   7,   7,   7,  // 6x
      7,   7,   7,   7, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
            (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
            (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
	
	if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        char log_char = pgm_read_byte(&code_to_name[keycode]);
        for (uint8_t j = 0; j < OLED_FONT_WIDTH; j++) {
            const uint8_t glyph_line = pgm_read_byte(&font[log_char * OLED_FONT_WIDTH + j]);
            next_log_byte[j] = glyph_line;
        }
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_sleep_timer = timer_read32();
        add_keylog(keycode);

        uint8_t t = next_bar_val + BAR_KEY_WEIGHT;
        if (t < next_bar_val) {
            next_bar_val = 255;
        } else {
            next_bar_val = t;
        }

        bar_key_decay = BAR_KEY_DECAY_MAX;
    }
    return true;
}

uint8_t render_layer_state(void) {
    uint8_t len = 0;
    oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY"), false);
            len = 6;
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            len = 5;
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            len = 5;
            break;
        case _GGG:
            oled_write_P(PSTR("GAME"), false);
            len = 4;
            break;
        case _SPECIAL:
            oled_write_P(PSTR("AGAME"), false);
            len = 5;
            break;
    }
    return len;
}

void render_mod_status(uint8_t modifiers) {
    //oled_write_P(PSTR("Mods: "), false);
    oled_write_char('S', (modifiers & MOD_MASK_SHIFT));
    oled_write_char('C', (modifiers & MOD_MASK_CTRL));
    oled_write_char('A', (modifiers & MOD_MASK_ALT));
    oled_write_char('G', (modifiers & MOD_MASK_GUI));
    //oled_write_char('\n', false);
}

void drawshit(char a1, char a2, char a3, char a4)
{
	static const char PROGMEM frame[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,128,192, 96, 96, 96, 96, 96, 96, 96,224, 96,224,224,224,224,224,224,224, 96,224, 96, 96, 96, 96, 96, 96, 96,224, 96,224,224,224,224,224,224,224, 96,224, 96, 96, 96, 96, 96, 96, 96,224, 96,224,224,224,224,224,224,224, 96,224, 96, 96, 96, 96, 96, 96, 96,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,126,255,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,126,129,255,255,255,129,126,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,126,129,255,255,255,129,126,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,126,129,255,255,255,129,126,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,255,126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  1,  3,  6,  6,  6,  6,  6,  6,  6,  7,  6,  7,  7,  7,  7,  7,  7,  7,  6,  7,  6,  6,  6,  6,  6,  6,  6,  7,  6,  7,  7,  7,  7,  7,  7,  7,  6,  7,  6,  6,  6,  6,  6,  6,  6,  7,  6,  7,  7,  7,  7,  7,  7,  7,  6,  7,  6,  6,  6,  6,  6,  6,  6,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
	
	static const int 
		y1 = 2,
		x1 = 1,
		x2 = 4,
		x3 = 7,
		x4 = 10;

	oled_write_raw_P(frame, sizeof(frame));

	oled_set_cursor(x1, y1);
	oled_write_char(a1, false);
	
	oled_set_cursor(x2, y1);
	oled_write_char(a2, false);
	
	oled_set_cursor(x3, y1);
	oled_write_char(a3, false);
	
	oled_set_cursor(x4, y1);
	oled_write_char(a4, false);
	
	oled_set_cursor(0, 0);
}

uint32_t frame_timer = 0;
void render_status_left(void) {
	if (timer_elapsed(frame_timer) > 1000){
		frame_timer = timer_read32();
		drawshit(rand()%10+'0', rand()%10+'0', rand()%10+'0', rand()%10+'0');
	}
    uint8_t len = render_layer_state();
    uint8_t t = 6 - len;
    if (t > len) {
        t = 0;
    }
    len = t + 4;

    for (; len; len--) {
        oled_write_char(' ', false);
    }
    render_mod_status(get_mods() | get_oneshot_mods());
}

uint8_t next_frame(void)
{
    uint8_t cur_speed = get_current_wpm();
    if (cur_speed > 0 && cur_speed < IDLE_SPEED)
    {
        return 2;
    }
    if (cur_speed > TAP_SPEED)
    {
        current_tap_frame = !current_tap_frame;
        return current_tap_frame;
    }
    if (current_idle_frame > (TAP_FRAMES - 2)) current_idle_frame = 2;
    current_idle_frame += 1;
    return current_idle_frame;
}


void oled_task_user(void) {
    // sleep if it has been long enough since we last got a char
    if (timer_elapsed32(oled_sleep_timer) > SLEEP_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }

    if (is_keyboard_left()) {
        render_status_left();
    } else {
    }

    // time for the next frame?
    if (timer_elapsed(anim_timer) > FRAME_TIMEOUT) {
        anim_timer = timer_read();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    anim_timer = timer_read();
    if (is_keyboard_left()) {
        return rotation;
    }  else {
        return OLED_ROTATION_180;
    }
}
