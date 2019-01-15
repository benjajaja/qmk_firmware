#include "xd75.h"

// Layer shorthand
#define _CO 0
#define _QW 1
#define _FN 2

// Shift when held, Enter when tapped
#define LSEN LSFT_T(KC_ENT)
#define RSEN RSFT_T(KC_ENT)

// Shift when held, Space when tapped
#define LSSP LSFT_T(KC_SPC)

// Shift when held, ALTGr when tappec
#define RALSPC RALT_T(KC_SPC)

// Cut/Paste shortcuts
#define PASTE RSFT(KC_INS)
#define CUT LSFT(KC_DEL)
#define CPY LCTL(KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* COLEMAK MOD-DH
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | HOME   | PG UP  | END    | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | B      | [      | PG DN  | ]      | J      | L      | U      | Y      | ;      |  \     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | BACKSP | A      | R      | S      | T      | G      | DEL    | INS    | `      | M      | N      | E      | I      | O      |  '     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | LSHENT | Z      | X      | C      | D      | V      | -      | UP     | =      | K      | H      | ,      | .      | /      | RSHENT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | MENU   | FUNCT  | RALSPC | LEFT   | DOWN   | LEFT   | RSHENT | FUNCT  | PRTSCR | RALT   | RGUI   | RCTL   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_CO] = { /* COLEMAK MOD-DH*/
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_PGUP, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_PGDN, KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS },
  { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_DEL,  KC_INS,  KC_GRV,  KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
  { LSEN,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MINS, KC_UP,   KC_EQL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RSEN    },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_MENU, MO(_FN), LSSP,    KC_LEFT, KC_DOWN, KC_RGHT, RSEN,    MO(_FN), KC_PSCR, KC_RALT, KC_RGUI, KC_RCTL },
 },
 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_PGUP, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_PGDN, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
  { KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL,  KC_INS,  KC_GRV,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  { LSEN,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_UP,   KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSEN    },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(_FN), LSSP,    KC_LEFT, KC_DOWN, KC_RGHT, RSEN,    MO(_FN), KC_PSCR, KC_RALT, KC_RGUI, KC_RCTL },
 },
/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F11    | RESET  | F12    | F6     | F7     | F8     | F9     | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | WWW    | MYCOMP | CALC   | MAIL   | RGB_TOG| M BTN3 | MW UP  | M BTN4 | RGB HD | RGB HI | MOD-DH | P7     | P8     | P9     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CAPSLK | PLAY   | PREV   | NEXT   | STOP   | RGB_MOD| MWLEFT | MWDOWM | MWRGTH | RGB SD | RGB SI | QWERTY | P4     | P5     | P6     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | MUTE   | VOL-   | VOL+   | MEDIA  | PASTE  | M BTN1 | M UP   | M BTN2 | RGB VD | RGB VI | CUT    | P1     | P2     | P3     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | M BTN1 | M BTN2 |        |        | M LEFT | M DOWN | M RGHT |        |        |        |        | P0     | P.     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_FN] = { /* FUNCTION */
//  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  RESET,   KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ },
//  { _______, KC_WSCH, KC_MYCM, KC_CALC, KC_MAIL, RGB_TOG, KC_BTN3, KC_WH_U, KC_BTN4, RGB_HUD, RGB_HUI, TG(_CO), KC_P7,   KC_P8,   KC_P9,  },
//  { KC_CAPS, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, RGB_MOD, KC_WH_L, KC_WH_D, KC_WH_R, RGB_SAD, RGB_SAI, TG(_QW), KC_P4,   KC_P5,   KC_P6,  },
//  { _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, PASTE,   KC_BTN1, KC_MS_U, KC_BTN2, RGB_VAD, RGB_VAI, CUT,     KC_P1,   KC_P2,   KC_P3,  },
//  { _______, _______, KC_BTN1, KC_BTN2, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_NLCK, KC_0,    KC_PDOT },

  { KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
  { KC_PSCR, KC_ESC,  CUT,     KC_WH_U, PASTE,   _______, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, _______ },
  { RGB_MOD, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, _______, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGUP, _______ },
  { RGB_TOG, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, _______, KC_P1,   KC_P2,   KC_P3,   _______, KC_HOME, KC_END,  KC_UP,   KC_PGDN, _______ },
  { RESET,   TG(_CO), TG(_QW), _______, _______, _______, KC_P0,   _______, KC_PDOT, KC_PENT, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______ },


//  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12   },
//  { KC_MSEL, KC_CALC, KC_MYCM, KC_MAIL, RGB_HUD, RGB_HUI, KC_P7,   KC_P8,   KC_P9,   KC_MINS, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS  },
//  { KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, RGB_SAD, RGB_SAI, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, _______, RESET,   _______, _______, _______  },
//  { KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  RGB_VAD, RGB_VAI, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, _______, _______, _______  },
//  { _______, _______, RGB_TOG, MO(_FN), RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, MO(_FN), _______, _______, _______  },
 }
};

// Runs boot tasks for keyboard
void matrix_init_user(void) {
  rgblight_enable();
  //rgblight_sethsv(150, 255, 255); // Spring Green
  //rgblight_sethsv(169, 255, 255); // Pulse Blue
  rgblight_sethsv(25, 255, 255); // Orange
  //rgblight_mode(13); // Swirling rainbow
  rgblight_mode(3);
}
