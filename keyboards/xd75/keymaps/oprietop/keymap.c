/* Copyright 2017 Wunder
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xd75.h"

// Layer shorthand
#define _CO 0
#define _QW 1
#define _FN 2

// Shift when held, Enter when tapped
#define KC_LSEN LSFT_T(KC_ENT)
#define KC_RSEN RSFT_T(KC_ENT)
// Shift when held, Space when tapped
#define KC_LSSP LSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK MOD-DH
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | `      | \      | 6      | 7      | 8      | 9      | 0      | DEL    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | B      | [      | ]      | J      | L      | U      | Y      | ;      | INS    | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | BACKSP | A      | R      | S      | T      | G      | NP DOT | '      | M      | N      | E      | I      | O      | RALT   | PW DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHENT | Z      | X      | C      | D      | V      | -      | =      | K      | H      | ,      | .      | /      |  UP    | RSHENT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | SUPER  | LALT   | MENU   | FUNCT  | LSHSPC | SPACE  | ENTER  | RSHENT | FUNCT  | HOME   | END    | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_CO] = { /* COLEMAK MOD-DH*/
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  KC_BSPC  },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_INS,  KC_PGUP  },
  { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_PDOT, KC_QUOT, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_RALT, KC_PGDN  },
  { KC_LSEN, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MINS, KC_EQL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSEN  },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_MENU, MO(_FN), KC_LSSP, KC_SPC,  KC_ENT,  KC_RSEN, MO(_FN), KC_HOME, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT  },
 },

 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  KC_BSPC  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_INS,  KC_PGUP  },
  { KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PDOT, KC_QUOT, KC_H,    KC_J,    KC_E,    KC_K,    KC_L,    KC_RALT, KC_PGDN  },
  { KC_LSEN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSEN  },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_MENU, MO(_FN), KC_LSSP, KC_SPC,  KC_ENT,  KC_RSEN, MO(_FN), KC_HOME, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT  },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | RESET  | F1     | F2     | F3     | F4     | F5     | F11    | F12    | F6     | F7     | F8     | F9     | F10    |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | WWW    | MYCOMP | CALC   | MAIL   |        | RGB HD | RGB HI | MOD-DH | P7     | P8     | P9     | M BTN3 | MW UP  | M BTN4 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CAPSLK | PLAY   | PREV   | NEXT   | STOP   |        | RGB SD | RGB SI | QWERTY | P4     | P5     | P6     | MWLEFT | MWDOWM | MWRGTH |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | MUTE   | VOL-   | VOL+   | MEDIA  |        | RGB VD | RGB VI |        | P1     | P2     | P3     | M BTN1 | M UP   | M BTN2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        | RGB TG | RGBMOD | RGBRMO | RGB TG |        | P0     | P.     | M LEFT | M DOWN | M RGHT |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_FN] = { /* FUNCTION */
  { RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______  },
  { _______, KC_WSCH, KC_MYCM, KC_CALC, KC_MAIL, _______, RGB_HUD, RGB_HUI,  TG(_CO), KC_P7,   KC_P8,   KC_P9,   KC_BTN3, KC_MS_U, KC_BTN4  },
  { KC_CAPS, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, _______, RGB_SAD, RGB_SAI,  TG(_QW), KC_P4,   KC_P5,   KC_P6,   KC_MS_L, KC_MS_D, KC_MS_R  },
  { _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, _______, RGB_VAD, RGB_VAI,  _______, KC_P1,   KC_P2,   KC_P3,   KC_BTN1, KC_MS_U, KC_BTN2  },
  { _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_TOG, _______, KC_0,    KC_PDOT, KC_MS_L, KC_MS_D, KC_MS_R  },
 }
};

// Runs boot tasks for keyboard
void matrix_init_user(void) {
        rgblight_enable();
        rgblight_sethsv(150, 255, 255); // Spring Green
        rgblight_mode(13); // Swirling rainbow
};


