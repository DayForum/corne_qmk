#pragma once

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define FORCE_NKRO

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLED_NUM 10
    #undef RGB_DI_PIN
    #define RGB_DI_PIN D3
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 5
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_ANIMATIONS
#endif



/* Make layout upside down = USB port on left side */
// #undef MATRIX_ROW_PINS
// #undef MATRIX_COL_PINS
//#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
// #define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }


