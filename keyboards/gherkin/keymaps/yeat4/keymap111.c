#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _GGG 3
#define _SPECIAL 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  GGG,
  SPECIAL
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_RESET RESET

#define KC_SRAISE LT(_RAISE, KC_SPC)
#define KC_SLOWER LT(_LOWER, KC_SPC)
#define KC_GG TO(_GGG)
#define KC_GGM MO(_SPECIAL)
#define KC_QWER TO(_QWERTY)
#define KC_LOW MO(_LOWER)
#define KC_RAIS MO(_RAISE)


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return TAPPING_TERM + 1250;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_ortho_3x10( \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_RSFT, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_Z,    KC_C,    KC_V,    KC_B,  KC_ENT,  KC_SPC,    KC_B,    KC_N,    KC_M,    KC_BSPC \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
  ),
  [_LOWER] = LAYOUT_ortho_3x10( \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
  ),

  [_RAISE] = LAYOUT_ortho_3x10( \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    KC_ESC,  KC_MINS, KC_EQL,  _______, KC_LBRC, KC_RBRC, _______, KC_QUOT, KC_SCLN, _______, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  _______, KC_TAB,  KC_BSLS, KC_COMM, KC_DOT,  KC_SLSH \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
  ),
  [_GGG] = LAYOUT_ortho_3x10( \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
  ),

  [_SPECIAL] = LAYOUT_ortho_3x10( \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET \
//,--------+-------+--------+--------+--------+--------+--------+--------+--------+----------.
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
