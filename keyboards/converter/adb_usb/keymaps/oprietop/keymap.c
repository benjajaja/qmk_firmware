#include QMK_KEYBOARD_H

// Timer for M_BSPC
static uint16_t timer;

// Layers
#define _QW 0
#define _DH 1
#define _LO 2
#define _RA 3
#define _AD 4

enum custom_keycodes {
  M_BSPC = SAFE_RANGE,
  M_WIPE,
  M_RAN64,
  UC_FLIP,
  UC_TABL,
  UC_SHRG,
  UC_DISA,
  UC_DANC,
  UC_SCRE,
  UC_WALL,
  UC_SOB,
  UC_DEAL,
  UC_RAGE,
  UC_NOOO,
  UC_SALU,
};

// Shortcuts
#define COPY LCTL(KC_INS)
#define CUT LSFT(KC_DEL)
#define PASTE RSFT(KC_INS)
#define KC_BL_S BL_STEP
#define KC_BL_B BL_BRTG

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
#define AD_ESC LT(_AD, KC_ESC)
#define LT_GUI LT(_AD, KC_RGUI)
#define LT_TAB LT(_LO, KC_TAB)
#define LO_SPC LT(_LO, KC_SPC)
#define S_SPC LSFT_T(KC_SPC)
#define S_TAB LSFT_T(KC_TAB)
#define S_DEL RSFT_T(KC_DEL)
#define RA_BSPC LT(_RA, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT_ext_iso(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,          KC_PSCR, KC_SLCK, KC_PAUS,                              DF(_DH),
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP,   KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_ENT , KC_DEL , KC_END , KC_PGDN,   KC_P7  , KC_P8  , KC_P9  , KC_PMNS,
      KC_LCAP, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS,                                       KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
      KC_LSFT, KC_NUBS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,                   KC_UP  ,            KC_P1  , KC_P2  , KC_P3  ,
      KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC ,                                     KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT,            KC_P0  , KC_PDOT, KC_PENT
  ),
  [_DH] = LAYOUT_ext_iso(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,          KC_PSCR, KC_SLCK, KC_PAUS,                              DF(_QW),
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC, KC_INS , KC_HOME, KC_PGUP,   KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST,
      KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_LBRC, KC_RBRC, KC_ENT , KC_DEL , KC_END , KC_PGDN,   KC_P7  , KC_P8  , KC_P9  , KC_PMNS,
      KC_LCAP, KC_A   , KC_R   , KC_S   , KC_T   , KC_G   , KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, KC_NUHS,                                       KC_P4  , KC_P5  , KC_P6  , KC_PPLS,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , KC_NUBS, KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,                   KC_UP  ,            KC_P1  , KC_P2  , KC_P3  ,
      KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC ,                                     KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT,            KC_P0  , KC_PDOT, KC_PENT
  ),
};

void matrix_init_user(void) { // Runs boot tasks for keyboard
  #ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
  #endif
};

static uint16_t bspc_role;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef OLED_DRIVER_ENABL
    if (record->event.pressed) {  add_keylog(keycode); }
  #endif
  switch (keycode) {
    // Our funky backspace key!
    case M_BSPC:
      if (get_mods() & MOD_BIT(KC_LSHIFT)) {
        bspc_role = KC_ENT;
      } else {
        bspc_role = KC_BSPC;
      }
      if (record->event.pressed) {
        if (timer_elapsed(timer) > TAPPING_TERM) {
          register_code(KC_RSFT);
        } else {
          register_code(bspc_role);
        }
        timer = timer_read();
      } else {
        // Unregister Right Shift if registered
        if (get_mods() & MOD_BIT(KC_RSHIFT)) {
          unregister_code(KC_RSFT);
        }
        // Check if we are into the TAPPING_TERM threshold
        if (timer_elapsed(timer) < TAPPING_TERM) {
          switch (bspc_role) {
            case KC_ENT:
              unregister_code(KC_LSFT);
              register_code(bspc_role);
              register_code(KC_LSFT);
            case KC_BSPC:
              register_code(bspc_role);
          }
        }
        unregister_code(bspc_role);
      }
      return false;
      break;
    case M_WIPE: // Wipe the eeprom and reset the board
      if (record->event.pressed) {
        eeconfig_init();
        reset_keyboard();
      }
      return false;
      break;
    case M_RAN64:
      if (record->event.pressed) {
        tap_random_base64();
      }
      return false;
      break;
    #ifdef UNICODE_ENABLE
      case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
        if (record->event.pressed) {
          send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
        }
        return false;
        break;
      case UC_TABL: // ┬─┬ノ( º _ ºノ)
        if (record->event.pressed) {
          send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029");
        }
        return false;
        break;
      case UC_SHRG: // ¯\_(ツ)_/¯
        if (record->event.pressed) {
          send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
        }
        return false;
        break;
      case UC_DISA: // ಠ_ಠ
        if (record->event.pressed) {
          send_unicode_hex_string("0CA0 005F 0CA0");
        }
        return false;
        break;
      case UC_DANC: // (〜￣△￣)〜
        if (record->event.pressed) {
          send_unicode_hex_string("0028 301C FFE3 25B3 FFE3 0029 301C");
        }
        return false;
        break;
      case UC_SCRE: // ヽ(ﾟДﾟ)ﾉ
        if (record->event.pressed) {
          send_unicode_hex_string("30FD 0028 FF9F 0414 FF9F 0029 FF89");
        }
        return false;
        break;
      case UC_WALL: // ┬┴┬┴┤(･_├┬┴┬┴
        if (record->event.pressed) {
          send_unicode_hex_string("252C 2534 252C 2534 2524 0028 FF65 005F 251C 252C 2534 252C 2534");
        }
        return false;
        break;
      case UC_SOB: // (ಢ⊱ಢ ｡)
        if (record->event.pressed) {
          send_unicode_hex_string("0028 0CA2 22B1 0CA2 0020 FF61 0029");
        }
        return false;
        break;
      case UC_DEAL: // ( ∙_∙) ( ∙_∙)>⌐■-■ (⌐■_■)
        if (record->event.pressed) {
          send_unicode_hex_string("0028 0020 2219 005F 2219 0029 0020 0028 0020 2219 005F 2219 0029 003E 2310 25A0 002D 25A0 0020 0028 2310 25A0 005F 25A0 0029");
        }
        return false;
        break;
      case UC_RAGE: // （╬ಠ益ಠ)
        if (record->event.pressed) {
          send_unicode_hex_string("FF08 256C 0CA0 76CA 0CA0 0029");
        }
        return false;
        break;
      case UC_NOOO: // (」ﾟﾛﾟ)｣NOOOooooo━
        if (record->event.pressed) {
          send_unicode_hex_string("0028 300D FF9F FF9B FF9F 0029 FF63 004E 004F 004F 004F 006F 006F 006F 006F 006F 2501");
        }
        return false;
        break;
      case UC_SALU: // (￣^￣)ゞ
        if (record->event.pressed) {
          send_unicode_hex_string("0028 FFE3 005E FFE3 0029 309E");
        }
        return false;
        break;
    #endif
  }
  return true;
};
