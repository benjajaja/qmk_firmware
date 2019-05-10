#include "xd75.h"

// Layers
#define _CO 0
#define _QW 1
#define _FN 2
#define _AD 3
// Shift when held, Enter when tapped
#define LSEN LSFT_T(KC_ENT)
#define RSEN RSFT_T(KC_ENT)
// Shift when held, Space when tapped
#define LSSP LSFT_T(KC_SPC)
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
  * | LCTRL  | LGUI   | LALT   | MENU   | FUNCT  | RALSPC | LEFT   | DOWN   | LEFT   | RSHENT | FUNCT  | CAPSL  | RALT   | RGUI   | RCTL   |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_CO] = { /* COLEMAK MOD-DH*/
    { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_PGUP, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
    { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_PGDN, KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS },
    { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_DEL,  KC_INS,  KC_GRV,  KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT },
    { LSEN,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MINS, KC_UP,   KC_EQL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RSEN    },
    { KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, TT(_FN), LSSP,    KC_LEFT, KC_DOWN, KC_RGHT, RSEN,    TT(_FN), KC_RALT, KC_LALT, KC_RGUI, KC_RCTL },
  },
  [_QW] = { /* QWERTY */
    { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
    { _______, _______, _______, KC_E,    KC_R,    KC_T,    _______, _______, _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______ },
    { _______, KC_A,    KC_S,    KC_D,    KC_F,    _______, _______, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______ },
    { _______, _______, _______, _______, KC_V,    KC_B,    _______, _______, _______, KC_N,    KC_M,    _______, _______, _______, _______ },
    { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  },
 /* FUNCTION
  * .--------------------------------------------------------------------------------------------------------------------------V------------.
  * | F11    | F1     | F2     | F3     | F4     | F5     | P/     | P*     | P-     | F6     | F7     | F8     | F9     | F10    | F12    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        | ESC    | CUT    | WH_UP  | PASTE  | VOL +  | P7     | P8     | P9     | PGUP   | MOU_B1 | MOU_UP | MOU_B2 | MOU_B3 |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        | TAB    | WH_LE  | WH_DO  | WH_RG  | VOL -  | P4     | P5     | P6     | HOME   | MOU_LE | MOU_DO | MOU_RG | PGUP   |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        | LCTL   | LSFT   | LGUI   | MOU_B1 | MUTE   | P1     | P2     | P3     | PGDN   | LEFT   | DOWN   | UP     | RIGHT  |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |        |        |        | ADJUST | SPACE  | P0     | P.     | P+     | PENT   | ADJUST |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_FN] = { /* FUNCTION */
    { KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PSLS, KC_PAST, KC_PMNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
    { _______, KC_ESC,  CUT,     KC_WH_U, PASTE,   KC_VOLU, KC_P7,   KC_P8,   KC_P9,   KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_BTN4 },
    { _______, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_VOLD, KC_P4,   KC_P5,   KC_P6,   KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_END,  _______ },
    { _______, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, KC_MUTE, KC_P1,   KC_P2,   KC_P3,   KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______ },
    { _______, _______, _______, _______, TT(_AD), KC_SPC,  KC_P0,   KC_PDOT, KC_PPLS, TT(_AD), _______, _______, _______, _______, _______ },
  },
 /* ADJUST
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * | F11    | F1     | F2     | F3     | F4     | F5     | P/     | P*     | P-     | F6     | F7     | F8     | F9     | F10    | F12    |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        | ESC    | CUT    | WH_UP  | PASTE  | VOL +  | P7     | P8     | P9     | PGUP   | MOU_B1 | MOU_UP | MOU_B2 | MOU_B3 | MOU_B4 |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * | RGB_MOD| TAB    | WH_LE  | WH_DO  | WH_RG  | VOL -  | P4     | P5     | P6     | HOME   | MOU_LE | MOU_DO | MOU_RG | PGUP   | FN TOG |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * | RGB_TOG| LCTL   | LSFT   | LGUI   | MOU_B1 | MUTE   | P1     | P2     | P3     | PGDN   | LEFT   | DOWN   | UP     | RIGHT  |        |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * | RESET  | CO/QW  | SCRLCK | PAUSE  | NUMLCK | SPACE  | P0     | P.     | P+     | PENT   | NUMLCK | LEFT   | DOWN   | RIGHT  |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_AD] = { /* ADJUST */
    { RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PSLS, KC_PAST, KC_PMNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12  },
    { _______, KC_ESC,  CUT,     KC_WH_U, PASTE,   KC_VOLU, KC_P7,   KC_P8,   KC_P9,   KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, _______ },
    { _______, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_VOLD, KC_P4,   KC_P5,   KC_P6,   KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_END,  _______ },
    { _______, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, KC_MUTE, KC_P1,   KC_P2,   KC_P3,   KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______ },
    { _______, TG(_QW), KC_SLCK, KC_PAUS, KC_NLCK, KC_SPC,  KC_P0,   KC_PDOT, KC_PPLS, KC_PENT, KC_NLCK, KC_LEFT, KC_DOWN, KC_RGHT, _______ },
  }
};

// Runs boot tasks for keyboard
void matrix_init_user(void) {
  rgblight_enable();
  //rgblight_sethsv(169, 255, 255); // Pulse CYAN
  rgblight_sethsv(25, 255, 255); // Orange
  //rgblight_sethsv(150, 255, 255); // Spring Green
  //rgblight_mode(13); // Swirling rainbow
  rgblight_mode(3);
}
