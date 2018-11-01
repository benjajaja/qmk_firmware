#include "xd75.h"

// Layer shorthand
#define _QW 0
#define _FN 1

// Shift when held, Enter when tapped
#define KC_LSEN LSFT_T(KC_ENT)
#define KC_RSEN RSFT_T(KC_ENT)

// Shift when held, Space when tapped
#define KC_LSSP LSFT_T(KC_SPC)

// ALTGR When held, Space when tapped
#define RALSPC RALT_T(KC_SPC)

// Cut/Paste shortcuts
#define PASTE RSFT(KC_INS)
#define CUT LSFT(KC_DEL)
#define CPY LCTL(KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | `      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | BACKSP | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | ENTER  | INS    | PG DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | LSHENT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHENT | HOME   | UP     | END    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | MENU   | FUNCT  | LSHSPC | RSHENT | FUNCT  | RALT   | RGUI   | RCTRL  | DEL    | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP },
  { KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_RSEN, KC_INS,  KC_PGDN },
  { KC_LSEN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSEN, KC_HOME, KC_UP,   KC_END },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_MENU, MO(_FN), RALSPC, KC_RSEN, MO(_FN), KC_RALT, KC_RGUI, KC_RCTL, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT },
 },
/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | RESET  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | WWW    | MYCOMP | CALC   | MAIL   | RGB_TOG| RGB HD | RGB HI | AGNORM | P7     | P8     | P9     | M BTN3 | MW UP  | M BTN4 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CAPSLK | PLAY   | PREV   | NEXT   | STOP   | RGB_MOD| RGB SD | RGB SI | AGSWAP | P4     | P5     | P6     | MWLEFT | MWDOWM | MWRGTH |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | MUTE   | VOL-   | VOL+   | MEDIA  | PASTE  | RGB VD | RGB VI | CUT    | P1     | P2     | P3     | M BTN1 | M UP   | M BTN2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | M BTN1 | M BTN2 |        |        |        |        |        |        | P0     | P.     | M LEFT | M DOWN | M RGHT |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 [_FN] = { /* FUNCTION */
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,   _______ },
  { _______, KC_WSCH, KC_MYCM, KC_CALC, KC_MAIL, RGB_TOG, RGB_HUD, RGB_HUI, AG_NORM, KC_P7,   KC_P8,   KC_P9,   KC_BTN3, KC_WH_U, KC_BTN4 },
  { KC_CAPS, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, RGB_MOD, RGB_SAD, RGB_SAI, AG_SWAP, KC_P4,   KC_P5,   KC_P6,   KC_WH_L, KC_WH_D, KC_WH_R },
  { _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, PASTE,   RGB_VAD, RGB_VAI, CUT,     KC_P1,   KC_P2,   KC_P3,   KC_BTN1, KC_MS_U, KC_BTN2 },
  { _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______, KC_NLCK, KC_0,    KC_PDOT, KC_MS_L, KC_MS_D, KC_MS_R },
 }
};

// Runs boot tasks for keyboard
void matrix_init_user(void) {
  rgblight_enable();
  //rgblight_sethsv(150, 255, 255); // Spring Green
  rgblight_sethsv(25, 255, 255); // Orange
  //rgblight_mode(13); // Swirling rainbow
  rgblight_mode(3);
}
