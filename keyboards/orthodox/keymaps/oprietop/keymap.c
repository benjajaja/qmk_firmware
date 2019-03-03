// oprietop's orthodox keyboard

#include QMK_KEYBOARD_H

extern rgblight_config_t rgblight_config;

// Timer for M_BSPC
static uint16_t timer;

// Default rgb brightness
static uint8_t brgt_val = 50;

// Layers
#define _DH 0
#define _QW 1
#define _LO 2
#define _RA 3
#define _MO 4

enum custom_keycodes {
  M_BSPC = SAFE_RANGE,
  M_VAD,
  M_VAI,
  M_RAN64,
  UC_FLIP,
  UC_TABL,
  UC_SHRG,
  UC_DISA,
  UC_DANC,
  UC_SCRE,
  UC_WALL,
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
#define MODESC LT(_MO, KC_ESC)
#define LOWTAB LT(_LO, KC_TAB)
#define MOVESPC LT(_LO, KC_SPC)
#define SFTBSPC SFT_T(KC_BSPC)
#define RAIDEL LT(_RA, KC_DEL)
#define GUIQUO RGUI_T(KC_QUOT)
#define LSSPC LSFT_T(KC_SPC)

// https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DH] = LAYOUT ( \
    KC_LBRC,      KC_Q,      KC_W,      KC_F, KC_P, AGT(KC_B),                                                      AGT(KC_J), KC_L, KC_U,    KC_Y,        KC_SCLN,      KC_RBRC,      \
    LST(KC_GRV),  KC_A,      KC_R,      KC_S, KC_T, KC_G,               KC_PIPE, MODESC,  KC_DEL, KC_BSLS,          KC_M,      KC_N, KC_E,    KC_I,        KC_O,         RST(KC_QUOT), \
    LCT(KC_MINS), LGT(KC_Z), TAT(KC_X), KC_C, KC_D, KC_V,      MO(_LO), LSSPC,   LOWTAB,  RAIDEL, M_BSPC,  MO(_RA), KC_K,      KC_H, KC_COMM, TAT(KC_DOT), RGT(KC_SLSH), RCT(KC_EQL)   \
  ),

  [_QW] = LAYOUT ( \
    _______, _______, _______, KC_E,    KC_R, AGT(KC_T),                                                         AGT(KC_Y), KC_U,    KC_I,    KC_O, KC_P,    _______, \
    _______, _______, KC_S,    KC_D,    KC_F, _______,            _______, _______,   _______, _______,          KC_H,      KC_J,    KC_K,    KC_L, KC_SCLN, _______, \
    _______, _______, _______, _______, KC_V, KC_B,      _______, _______, _______,   _______, _______, _______, KC_N,      KC_M, _______, _______, _______, _______  \
  ),

  [_LO] = LAYOUT ( \
    _______, KC_ESC,  COPY,    KC_WH_U, CUT,     PASTE,                                                         KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, _______, \
    _______, KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_INS,          _______, _______,   KC_ENT,  KC_UP,           KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_END,  _______, \
    _______, KC_LCTL, KC_LSFT, KC_LGUI, KC_BTN1, KC_DEL, _______, _______, _______,   A(KC_B), KC_ENT, A(KC_F), KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______  \
  ),

  [_RA] = LAYOUT ( \
    KC_PIPE, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, \
    KC_DOT,  KC_1,    KC_2,  KC_3,    KC_4,   KC_5,             _______, _______,   C(KC_W), A(KC_D),          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_COMM, \
    KC_F11,  KC_F1,   KC_F2, KC_F3,   KC_F4,  KC_F5,   _______, KC_ENT,  _______,   C(KC_U), C(KC_K), _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12   \
  ),

  [_MO] = LAYOUT ( \
    RESET,   KC_ACL0,  KC_ACL1, KC_ACL2, _______, _______,                                                         _______, _______, _______, TSKMGR,  CALTDEL, KC_PSCR, \
    TG(_QW), RGB_RMOD, RGB_HUI, RGB_SAI, M_VAI,   _______,          _______, _______,   M_RAN64, _______,          UC_FLIP, UC_TABL, UC_SHRG, UC_DISA, _______, _______, \
    RGB_TOG, RGB_MOD,  RGB_HUD, RGB_SAD, M_VAD,   _______, _______, _______, _______,   _______, _______, _______, UC_DANC, UC_SCRE, UC_WALL, _______, _______, _______  \
  ),

};

// https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h
void matrix_init_user(void) { // Runs boot tasks for keyboard
    set_unicode_input_mode(UC_LNX);
    rgblight_enable();
    //rgblight_sethsv(276,255,170); // Purple
    rgblight_sethsv(0,0,brgt_val); // White
    rgblight_mode(21);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Our funky backspace key!
    case M_BSPC:
      if (record->event.pressed) {
        timer = timer_read();
        // Register Right Shift if we are not shifted
        if (! (get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)))) {
          register_code(KC_RSFT);
        }
      } else {
        // Unregister Right Shift if registered
        if (get_mods() & MOD_BIT(KC_RSHIFT)) {
          unregister_code(KC_RSFT);
        }
        // Check if we are into the TAPPING_TERM threshold
        if (timer_elapsed(timer) < TAPPING_TERM) {
          // Tap Enter if left shifted, Backspace if not
          if (get_mods() & MOD_BIT(KC_LSHIFT)) {
            // Avoid sending Left Shift + Enter
            unregister_code(KC_LSFT);
            tap_code(KC_ENT);
            register_code(KC_LSFT);
          } else {
            tap_code(KC_BSPC);
          }
        }
      }
      return false;
    case M_VAD:
      if (record->event.pressed) {
          rgblight_decrease_val();
          brgt_val = rgblight_config.val;
      }
      return false;
    case M_VAI:
      if (record->event.pressed) {
          rgblight_increase_val();
          brgt_val = rgblight_config.val;
      }
      return false;
    case M_RAN64:
      if (record->event.pressed) {
          tap_random_base64();
      }
      return false;
    #ifdef UNICODE_ENABLE
      case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
        if (record->event.pressed) {
          send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
        }
        break;
      case UC_TABL: // ┬─┬ノ( º _ ºノ)
        if (record->event.pressed) {
          send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029");
        }
        break;
      case UC_SHRG: // ¯\_(ツ)_/¯
        if (record->event.pressed) {
          send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
        }
        break;
      case UC_DISA: // ಠ_ಠ
        if (record->event.pressed) {
          send_unicode_hex_string("0CA0 005F 0CA0");
        }
        break;
      case UC_DANC: // (〜￣△￣)〜
        if (record->event.pressed) {
          send_unicode_hex_string("0028 301C FFE3 25B3 FFE3 0029 301C");
        }
        break;
      case UC_SCRE: // ヽ(ﾟДﾟ)ﾉ
        if (record->event.pressed) {
          send_unicode_hex_string("30FD 0028 FF9F 0414 FF9F 0029 FF89");
        }
        break;
      case UC_WALL: // ┬┴┬┴┤(･_├┬┴┬┴
        if (record->event.pressed) {
          send_unicode_hex_string("252C 2534 252C 2534 2524 0028 FF65 005F 251C 252C 2534 252C 2534");
        }
        break;
    #endif
  }
  return true;
};

// Change LED colors depending on the layer.
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _DH:
      rgblight_sethsv(0,0,brgt_val); // White
      break;
    case _QW:
      rgblight_sethsv(276,255,brgt_val); // Purple
      break;
    case _LO:
      rgblight_sethsv(39,255,brgt_val); // Orange
      break;
    case _RA:
      rgblight_sethsv(160,255,brgt_val); // Green
      break;
    case _MO:
      rgblight_sethsv(0,255,brgt_val); // Red
      break;
  }
  return state;
};
