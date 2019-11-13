#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

#ifdef OLED_DRIVER_ENABLE
static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
#endif

// Layers
#define _QW 0
#define _WM 1
#define _RA 2
#define _AD 3

enum custom_keycodes {
  MODDH  = SAFE_RANGE,
  M_BSPC,
  M_WIPE,
  M_RAN64,
  UC_FLIP,
  UC_SHRG,
  UC_DISA,
  UC_CRY,
};

// Shortcuts
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
#define LT_ESC LT(_AD, KC_ESC)
#define LT_GUI LT(_AD, KC_RGUI)
#define LT_TAB LT(_LO, KC_TAB)
#define LT_DEL LT(_RA, KC_DEL)
#define LT_SPC LT(_LO, KC_SPC)
#define S_SPC LSFT_T(KC_SPC)
#define S_TAB LSFT_T(KC_TAB)
#define S_DEL RSFT_T(KC_DEL)
#define LT_BSPC LT(_RA, KC_BSPC)

#define MOD4 LM(_WM, MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.         ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |         |   Y  |   U  |   I  |   O  |   P  |Backsp|
   * |------+------+------+------+------+------|         |------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |         |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|         |------+------+------+------+------+------|
   * |-/LCTR|Z/LGUI|X/LALT|   C  |   V  |   B  |         |   N  |   M  |   ,  |./LALT|/_RGUI|=/RCTR|
   * `------+------+------+------+------+------+---. ,---+------+------+------+------+------+------'
   *                          | Mod4 |Shift|Spac/Ra| |Entr/Ra|Shift|   Lo |
   *                          `--------------------' `--------------------'
   */
  [_QW] = LAYOUT (
    KC_TAB,      KC_Q,     KC_W,     KC_E, KC_R, KC_T,            KC_Y, KC_U, KC_I,    KC_O,        KC_P,         KC_BSPC, \
    KC_ESC,      KC_A,     KC_S,     KC_D, KC_F, KC_G,            KC_H, KC_J, KC_K,    KC_L,        KC_SCLN,      KC_QUOT, \
    LCT(KC_MINS),TAT(KC_Z),LGT(KC_X),KC_C, KC_V, KC_B,            KC_N, KC_M, KC_COMM, RGT(KC_DOT), AGT(KC_SLSH), RCT(KC_EQL),\
                       MOD4, KC_LSPO, LT(_RA, KC_SPC),            LT(_RA, KC_ENT), KC_RSPC, MO(_AD) \
  ),
  /* Raise
   * ,-----------------------------------------.         ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |         |   ^  |   &  |   *  |   (  |   )  |   \  |
   * |-------------+------+------+------+------|         |------+------+------+------+------+------|
   * |   `  |   {  | PgUp |PgDown|  End | Home |         | Left | Down |  Up  | Down |   }  |   |  |
   * |-------------+------+------+------+------|         |------+------+------+------+------+------|
   * |   [  |   1  |   2  |   3  |   4  |   5  |         |   6  |   7  |   8  |   9  |   0  |   ]  |
   * `------+------+------+------+------+------+---. ,---+------+------+------+------+------+------'
   *                          |      |      |Enter | |      |      |      |
   *                          `--------------------' `--------------------'
   */
  [_RA] = LAYOUT (
    KC_TILD, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, \
    KC_GRV,  KC_LCBR, KC_PGUP,KC_PGDN, KC_END,  KC_HOME,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCBR, KC_PIPE, \
    KC_LBRC, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_RBRC, \
                             XXXXXXX, XXXXXXX, KC_ENT, _______, XXXXXXX, XXXXXXX \
  ),
  /* XMonad window manager shortcuts.
   * Needs MOD_LGUI
   * ,-----------------------------------------.         ,-----------------------------------------.
   * |   Q  |   1  |   2  |   3  |   4  |   5  |         |   6  |   7  |   8  |   9  |   P  |      |
   * |-------------+------+------+------+------|         |------+------+------+------+------+------|
   * |LShift|      |      |      |      |   T  |         |   H  |   J  |   K  |   L  |      |      |
   * |-------------+------+------+------+------|         |------+------+------+------+------+------|
   * |      |      |      |   C  |      |   B  |         |      |      |      |      |      |      |
   * `------+------+------+------+------+------+---. ,---+------+------+------+------+------+------'
   *                          |      |LShift|      | |Enter |      |      |
   *                          `--------------------' `--------------------'
   */
  [_WM] = LAYOUT (
    KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_P,    XXXXXXX, \
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_T,        KC_H,    KC_J,    KC_K,    KC_L,    XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_C,    XXXXXXX, KC_B,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                               KC_LSFT, XXXXXXX, XXXXXXX,     KC_ENT,  XXXXXXX, XXXXXXX \
  ),
  // F1-12, RGB, Gimmicks
  [_AD] = LAYOUT (
    XXXXXXX, RGB_RMOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,           UC_FLIP, UC_DISA, UC_SHRG, UC_CRY,  XXXXXXX, XXXXXXX, \
    RGB_TOG, RGB_MOD,  RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
    KC_F11,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
                                XXXXXXX, M_RAN64, XXXXXXX,           KC_BSPC, _______, XXXXXXX \
  ),
};

void matrix_init_user(void) { // Runs boot tasks for keyboard
  #ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
  #endif
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return rotation;
}
/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { */
  /* if (is_master) { */
    /* return rotation;//OLED_ROTATION_270; */
  /* } else { */
    /* return rotation; */
  /* } */
/* } */



void render_bootmagic_status(void) {
  if (keymap_config.swap_lalt_lgui) {
    oled_write_P(PSTR("Mac "), false);
  } else {
    oled_write_P(PSTR("HID "), false);
  }

  oled_write_P(PSTR("QWERTY "), false);
}

void render_layer_state(void) {
  switch (biton32(layer_state)) {
    case 0:
      oled_write_P(PSTR("NUL "), false);
      break;
    case _WM:
      oled_write_P(PSTR("XMN "), false);
      break;
    case _RA:
      oled_write_P(PSTR("RSE "), false);
      break;
    case _AD:
      oled_write_P(PSTR("ADJ "), false);
      break;
    default:
      oled_write_P(PSTR("ERR "), false);
      break;
  }
}

static char* dec_to_str(uint32_t val) {
  static char str [2] = {'0', '0'};
  str[0] = val / 10 + 48;
  str[1] = val % 10 + 48;
  return str;
}

void render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR("leds:"), true);

  /* uint8_t mode = rgb_matrix_get_mode(); */
  /* static char str [2] = {'X', 'Y'}; */
  /* str[0] = mode / 10 + 48; */
  /* str[1] = mode % 10 + 48; */
  oled_write_P(PSTR("12345"), false);
  /* oled_write_P(str, false); */

  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("CAPS"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("SCRL"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("GUI "), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("ALT "), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("      "), false);
}

void render_crkbd_logo(void) {
  oled_write_P(PSTR("                     "), false); // one empty row to center on display
  oled_write_P(crkbd_logo, false);
}

void render_status_debug(void) {
  render_bootmagic_status();
  render_layer_state();

  oled_write_P(PSTR("A"), false);
  oled_write(dec_to_str(rgb_matrix_get_mode()), false);

  oled_write_P(PSTR(" F"), false);
  oled_write(dec_to_str(rgb_matrix_get_flags()), false);
}

void oled_task_user(void) {
  if (biton32(layer_state) != 0) {
    oled_scroll_off();
    render_status_debug();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    uint8_t modifiers = get_mods()|get_oneshot_mods();
    if (modifiers != 0) {
      oled_scroll_off();
      render_mod_status(modifiers);
    } else {
      render_crkbd_logo();
      oled_scroll_left(); // Turns on scrolling
    }
  }
}
#endif

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_keymap(void) {
  rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
  rgb_matrix_set_suspend_state(false);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
      // Some Emojis
      // https://r12a.github.io/app-conversion/
      // https://gist.github.com/endolith/157796
      // case UC_: //
      //   if (record->event.pressed) {
      //     send_unicode_hex_string("");
      //   }
      //   return false;
      //   break;
      case UC_CRY: // ಥ_ಥ
        if (record->event.pressed) {
          send_unicode_hex_string("0CA5 005F 0CA5");
        }
        return false;
        break;
      case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
        if (record->event.pressed) {
          send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
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
    #endif
  }
  return true;
};

