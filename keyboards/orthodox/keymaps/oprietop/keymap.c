// oprietop's orthodox keyboard

#include QMK_KEYBOARD_H

// Layers
#define _MODDH 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _MOVE 4

enum custom_keycodes {
  MODDH = SAFE_RANGE,
  QWERTY,
};

// Shortcuts
#define ADJUST MO(_ADJUST)
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define COPY LCTL(KC_INS)
#define CUT LSFT(KC_DEL)
#define PASTE RSFT(KC_INS)

// Mod-Taps
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
#define LST(X) LSFT_T(X)
#define RST(X) RSFT_T(X)
#define LCT(X) LCTL_T(X)
#define RCT(X) RCTL_T(X)
#define LGT(X) LGUI_T(X)
#define RGT(X) RGUI_T(X)
#define TAT(X) LALT_T(X)
#define AGT(X) RALT_T(X)

// Thumbs
#define CTLESC CTL_T(KC_ESC)
#define LOWTAB LT(_LOWER, KC_TAB)
#define MOVESPC LT(_MOVE, KC_SPC)
#define SFTBSPC SFT_T(KC_BSPC)
#define RAIDEL LT(_RAISE, KC_DEL)
#define GUIQUO RGUI_T(KC_QUOT)

// https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MODDH] = LAYOUT ( \
  KC_ESC,  KC_Q,      KC_W,      KC_F,      KC_P, AGT(KC_B),                                                       AGT(KC_J), KC_L, KC_U,         KC_Y,        KC_SCLN,      KC_BSPC, \
  KC_TAB,  LST(KC_A), KC_R,      KC_S,      KC_T, KC_G,              RESET,   _______,   _______, _______,         KC_M,      KC_N, KC_E,         KC_I,        RST(KC_O),    KC_QUOT, \
  KC_LSFT, LCT(KC_Z), LGT(KC_X), TAT(KC_C), KC_D, KC_V,      LOWTAB, MOVESPC, CTLESC,    GUIQUO,  SFTBSPC, RAIDEL, KC_K,      KC_H, TAT(KC_COMM), RGT(KC_DOT), RCT(KC_SLSH), KC_RSFT  \
),

[_QWERTY] = LAYOUT ( \
  _______, _______, _______, KC_E,    KC_R, AGT(KC_T),                                                         AGT(KC_Y), KC_U,    KC_I,    KC_O, KC_P,         _______, \
  _______, _______, KC_S,    KC_D,    KC_F, _______,            _______, _______,   _______, _______,          KC_H,      KC_J,    KC_K,    KC_L, RST(KC_SCLN), _______, \
  _______, _______, _______, _______, KC_V, KC_B,      _______, _______, _______,   _______, _______, _______, KC_N,      KC_M, _______, _______, _______,      _______  \
),

[_LOWER] = LAYOUT ( \
  RESET, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  MODDH, KC_CAPS, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP,          RESET,   _______,   _______, KC_UP,         KC_GRV,  KC_QUOT, KC_DQT,  KC_LCBR, KC_RCBR, _______, \
  QWERTY, KC_PSCR, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL, _______, _______, _______,   KC_LEFT, KC_DOWN,  KC_RGHT, KC_TILD, KC_BSLS, KC_PIPE, KC_LBRC, KC_RBRC, _______  \
),

[_RAISE] = LAYOUT ( \
  _______, KC_1,  KC_2,  KC_3,  KC_4,   KC_5,                                                          KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,           _______, _______,   _______, _______,         KC_F6,  KC_MINS, KC_EQL,  KC_PLUS, KC_ASTR, _______, \
  _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, _______, _______, _______,   _______, _______, KC_ENT, KC_F12, KC_UNDS, _______, _______, _______, _______  \
),

[_MOVE] = LAYOUT ( \
  _______, KC_ESC,  COPY,    KC_WH_U, CUT,     PASTE,                                                         KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_PGUP, _______, \
  _______, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_INS,          _______, _______,   _______, _______,         KC_MS_L, KC_MS_D, KC_MS_R, KC_UP,   KC_PGDN, _______, \
  _______, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, KC_DEL, _______, _______, _______,   _______, KC_ENT,  KC_ENT, KC_HOME, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, _______  \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MODDH:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MODDH);
        SEND_STRING("\nLayout changed to COLEMAK MOD-DH.\n");
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
        SEND_STRING("\nLayout changed to QWERTY.\n");
      }
      return false;
      break;
  }
  return true;
};
