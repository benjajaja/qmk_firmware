/* This is the Zen keyboard layout by oprietop

TODO:

 * Figure the best approach for the 1,5 keys.
 * Still not convinded on the thumbs too.
 * Determine if i want/need the raise layer and finish/remove it.

*/

#include QMK_KEYBOARD_H

// Allow printing version info
#include "version.h"

extern keymap_config_t keymap_config;

enum layers {
  _MODDH,
  _QWERTY,
  _LOWER,
  _RAISE,
};

enum keycodes {
  // Layers
  MODDH = SAFE_RANGE,
  QWERTY,
  // Macros
  KC_VER,
  KC_PULL,
  KC_PUSH,
  KC_LS,
  KC_INCL,
};

// Cut/Paste shortcuts
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

// Modifiers 
#define OS_ALT OSM(MOD_LALT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_GUI OSM(MOD_LGUI)
#define LT_ESC LT(_RAISE, KC_ESC)
#define LT_SPC LT(_LOWER, KC_SPC)
#define S_TAB LSFT_T(KC_TAB)
#define S_DEL RSFT_T(KC_DEL)
#define LT_BSPC LT(_LOWER, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MODDH] = LAYOUT( \
    KC_ESC,  KC_1,      KC_2,    KC_3,   KC_4,   KC_5,                    KC_6,      KC_7,    KC_8,    KC_9,   KC_0,      KC_BSPC, \
    KC_LBRC, KC_Q,      KC_W,    KC_F,   KC_P,   AGT(KC_B),               AGT(KC_J), KC_L,    KC_U,    KC_Y,   KC_SCLN,   KC_RBRC, \
    KC_GRV,  LST(KC_A), KC_R,    KC_S,   KC_T,   KC_G,                    KC_M,      KC_N,    KC_E,    KC_I,   RST(KC_O), KC_QUOT, \
    KC_MINS, KC_Z,      KC_X,    KC_C,   KC_D,   KC_V,                    KC_K,      KC_H,    KC_COMM, KC_DOT, KC_SLSH,   KC_EQL,  \
    KC_LCTL, KC_LGUI,   KC_LALT, KC_ENT, LT_ESC, LT_SPC,    S_TAB, S_DEL, LT_BSPC,   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,   KC_BSLS  \
  ),

  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC, \
    KC_LBRC, KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                 KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_RBRC, \
    KC_GRV,  KC_A,   KC_R,   KC_S,   KC_T,   KC_G,                 KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT, \
    KC_MINS, KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,                 KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, KC_EQL,  \
    KC_BSLS, OS_CTL, OS_GUI, OS_ALT, LT_ESC, KC_SPC, LT_SPC, S_DEL, LT_BSPC, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_PIPE  \
  ),

  [_LOWER] = LAYOUT( \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
    KC_LCBR, KC_ESC,  CUT,     KC_WH_U, PASTE,   KC_LBRC,                  KC_RBRC, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_RCBR, \
    KC_TILD, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_GRV,                   KC_QUOT, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGUP, KC_DQUO, \
    KC_UNDS, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, KC_MINS,                  KC_EQL,  KC_HOME, KC_END,  KC_UP,   KC_PGDN, KC_PLUS, \
    _______, _______, _______, _______, _______, KC_ENT,  KC_SPC, KC_BSPC, KC_ENT,  KC_PIPE, KC_LEFT, KC_DOWN, KC_RGHT, KC_PIPE  \
  ),

  [_RAISE] = LAYOUT( \
    RESET,  RGB_TOG,  MODDH, QWERTY,  KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
    KC_TILD, KC_GRV,  _______, _______, _______, _______,                   MODDH, QWERTY,  _______, _______, _______, KC_PIPE, \
    _______, _______, RGB_M_P, RGB_M_B, RGB_M_R, _______,                   _______, QWERTY,  _______, _______, _______, _______, \
    RGB_TOG, RGB_MOD, _______, RGB_M_K, RGB_M_G, RGB_HUI,                   RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, \
    _______, _______, _______, KC_HOME, KC_END,  KC_DEL,  _______, _______, KC_INS,  KC_PGUP, KC_PGDN, _______, _______, _______ \
  ),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Layers
    case MODDH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MODDH);
        SEND_STRING("\nLayout changed to COLEMAK MOD-DH.\n");
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        SEND_STRING("\nLayout changed to QWERTY.\n");
      }
      return false;
    // Macros
    case KC_INCL:
      if (record->event.pressed) {
        SEND_STRING("#include <>"SS_TAP(X_LEFT));
      }
      return false;
    case KC_PULL:
      if (record->event.pressed) {
        SEND_STRING("git pull"SS_TAP(X_ENTER));
      }
      return false;
    case KC_PUSH:
      if (record->event.pressed) {
        SEND_STRING("git push"SS_TAP(X_ENTER));
      }
      return false;
    case KC_LS: 
      if (record->event.pressed) {
        SEND_STRING("ls -la"SS_TAP(X_ENTER));
      }
      return false;
    case KC_VER:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION "@" QMK_BUILDDATE);
      }
      return false;
  }
  return true;
}
