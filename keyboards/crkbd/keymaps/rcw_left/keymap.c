#include QMK_KEYBOARD_H

#ifdef OLED_DRIVER_ENABLE
  #include "oled.h"
#endif

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  LBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       ENT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,   BSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT,   LOW,  LSFT,      SPC, RAIS, LGUI \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC, XXXXX,     7,     8,     9,  CLCK,                     F1,   F2,    F3,   F4,     F5,    F6, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,     0,    4,    5,    6,   INSERT,                   LEFT,  DOWN,    UP, RIGHT,   F11,   F12,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS, XXXXX,    1,    2,    3,    XXXXX,                     F7,   F8,    F9,   F10,   GG,    TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT,  TRNS,   LSFT,     SPC,  RSFT, LGUI \
                               //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,  EXLM,   AT,  HASH,   DLR,  PERC,                    CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  TILD,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS, XXXXX, HOME,  PGUP,  DEL,  PSCR,                    MINS,   EQL,  LCBR,  RCBR,  PIPE,  TILD,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS, XXXXX,  END,  PGDN, XXXXX, XXXXX,                    UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT,   LOW,  LSFT,      SPC, TRNS, LGUI \
                              //`--------------------'  `--------------------'
  ),
  [_GGG] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      KC_T, KC_TAB, KC_Q, KC_W,  KC_E,  KC_R,                    KC_Y, KC_U,  KC_I,  KC_O, KC_P, KC_LBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_G, KC_LSFT,KC_A, KC_S,  KC_D,  KC_F,                    KC_H, KC_J,  KC_K,  KC_L, KC_SCLN, KC_QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_B, KC_LCTL,KC_Z, KC_X,  KC_C,  KC_V,                    KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_BSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LALT,KC_GGM,KC_SPC,  KC_QWER,KC_ENT,KC_SPC \
                              //`--------------------'  `--------------------'
  ),

  [_SPECIAL] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2, TRNS,     3,     4,                       F1,   F2,    F3,   F4,     F5,    F6,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          M,     5,  TRNS, TRNS, TRNS,      6,                    LEFT,  DOWN,    UP, RIGHT,  LBRC,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          L, TRNS,     7,     8,     9,     0,                     F7,   F8,    F9,   F10,   F11,   F12,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  L,    TRNS,  TRNS,      LOW, TRNS, TRNS \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#ifdef OLED_DRIVER_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // tell the oled code about the key
  process_record_user_oled(keycode, record);

  switch (keycode) {
    case SPECIAL:
      if (record->event.pressed) {
          layer_on(_SPECIAL);
      } else {
          layer_off(_SPECIAL);
      }
      return false;

  }
  return true;
}
#endif

void matrix_scan_user(void) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);
  if (old_layer != new_layer) {
    switch (new_layer) {
      case _QWERTY:
        rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
      break;
      case _LOWER:
        rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
      break;
      case _RAISE:
        rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
      break;
      case _GGG:
        rgb_matrix_mode(RGB_MATRIX_BAND_SAT);
      break;
      case _SPECIAL:
        rgb_matrix_mode(RGB_MATRIX_BAND_SAT);
      break;
    }
    old_layer = new_layer;
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          econfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}
