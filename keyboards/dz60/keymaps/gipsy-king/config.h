#pragma once

#undef MANUFACTURER
#define MANUFACTURER    Benja

#undef PRODUCT
#define PRODUCT         EL TECLADO

#undef RGBLED_NUM
#define RGBLED_NUM 48

#undef UNICODE_KEY_OSX
#define UNICODE_KEY_OSX KC_RALT

// #undef RGBLIGHT_LED_MAP
// #define RGBLIGHT_LED_MAP { 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 }

/////////////////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"

#define RETRO_TAPPING

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x2260
#define DEVICE_VER      0x0001
#define MANUFACTURER    Benja
#define PRODUCT         EL_TECLADO
#define DESCRIPTION     El Teclado Definitivo

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { F0, F1, E6, C7, C6, B7, D4, B1, B0, B5, B4, D7, D6, B3, F4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 5

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN E2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_LED_MAP { 16, 17, 18, 19, 20, 21, 22, 23 }
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

/* sets 'Auto Shift' timeouts */
// #define AUTO_SHIFT_TIMEOUT 150
// #define NO_AUTO_SHIFT_SPECIAL

#endif
