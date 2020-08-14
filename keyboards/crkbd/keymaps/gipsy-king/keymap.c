#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

void lines_init(void);

#ifdef OLED_DRIVER_ENABLE
#define PROMPT_WIDTH 21
#define PROMPT_LINES 5
#define PROMPT_SIZE (PROMPT_WIDTH * PROMPT_LINES)
char prompt_buffer[PROMPT_SIZE];
/* static const char PROGMEM crkbd_logo_1[64] = { */
  /* 0x80, 0x81, 0x82, 0x83, 0x84, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, */
  /* 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, */
  /* 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0}; */
/* static const char PROGMEM crkbd_logo_1[64] = { */
  /* 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, */
  /* 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, */
  /* 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0}; */
/* static const char PROGMEM crkbd_logo_2[64] = { */
  /* 0x89, 0xa9, 0xc9, */
  /* 0x88, 0xa8, 0xc8, */
  /* 0x87, 0xa7, 0xc7, */
  /* 0x86, 0xa6, 0xc6, */
  /* 0x85, 0xa5, 0xc5, */
  /* 0}; */
/* static const char PROGMEM crkbd_logos[] = { */
  /* {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,  */
   /* 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,  */
   /* 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0}; */
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
      KC_LSFT, XXXXXXX, KC_SPC,     KC_ENT,  XXXXXXX, XXXXXXX \
      ),
  // F1-12, RGB, Gimmicks
  [_AD] = LAYOUT (
      M_WIPE, RGB_RMOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU,           UC_FLIP, UC_DISA, UC_SHRG, UC_CRY,  XXXXXXX, XXXXXXX, \
      RGB_TOG, RGB_MOD,  RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
      KC_F11,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      XXXXXXX, M_RAN64, XXXXXXX,           KC_BSPC, _______, XXXXXXX \
      ),
};

void keyboard_post_init_user(void) {
  /* debug_enable=true; */
}

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
  lines_init();
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_0;
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

#ifdef RGB_MATRIX_ENABLE
static char* dec_to_str(uint32_t val) {
  static char str [3] = {'0', '0', 0};
  str[0] = val / 10 + 48;
  str[1] = val % 10 + 48;
  return str;
}
#endif

static uint8_t prompt_cursor = 0;
static uint8_t prompt_buffer_line = 0;
static uint8_t prompt_screen_line = 0;
static uint8_t prompt_scroll = 0;
static uint16_t prompt_timer = 0;
static uint16_t prompt_timeout_timer = 0;
static bool prompt_blink = false;
static uint8_t prompt_blink_cursor = 0;
enum prompt_info {
  INFO_WPM,
#ifdef RGB_MATRIX_ENABLE
  INFO_ANIMATION,
  INFO_SPEED,
  INFO_HSV,
#endif
  INFO_LAYERS,
};
#define INFO_SIZE INFO_LAYERS
static uint8_t prompt_info_cursor = INFO_WPM;
static uint16_t prompt_info_layer_activations = 0;

uint8_t prompt_find_empty(void) {
  uint8_t line = prompt_buffer_line;
  for (uint8_t i = 0; i < PROMPT_LINES; i++) {
    if (prompt_buffer[line * PROMPT_WIDTH] == 0) {
      return line;
    }
    line++;
    if (line >= PROMPT_LINES) {
      line = 0;
    }
  }
  return 255;
}


void prompt_add(const char *data) {
  // find spot
  uint8_t line = prompt_find_empty();
  if (line == 255) {
#ifdef CONSOLE_ENABLE
    uprintf("no space to add string");
#endif
    // no space
    return;
  }
  uint8_t i = 0;
  uint8_t c = data[i];
  while (c != 0 && i < PROMPT_WIDTH - 1) {
    prompt_buffer[line * PROMPT_WIDTH + i] = c;
    i++;
    c = data[i];
  }
  prompt_buffer[line * PROMPT_WIDTH + i] = 0;
}

static char prompt_add_P_buffer[21];
void prompt_add_P(const char *data) {
  strcpy_P(prompt_add_P_buffer, data);
  prompt_add(prompt_add_P_buffer);
}

static char prompt_add_f_buffer[21];
void prompt_add_f(const char *format, ...) {
  va_list args;
  va_start (args, format);
  vsprintf(prompt_add_f_buffer, format, args);
  prompt_add(prompt_add_f_buffer);
}

void lines_init(void) {
  for (uint8_t i = 0; i < PROMPT_SIZE; i++) {
    prompt_buffer[i] = 0;
  }
  prompt_add_P(PSTR("qmk ready"));

  const uint8_t layer_count = sizeof(keymaps) / sizeof(keymaps[0]);
  prompt_add_f("%d layers", layer_count);

  prompt_add_P(PSTR("oled screen ready"));

  prompt_add_P(PSTR("crkbd initalized"));

  prompt_cursor = 0;
  prompt_scroll = 0;
  prompt_buffer_line = 0;
  prompt_screen_line = 0;
  prompt_timer = timer_read();
  prompt_timeout_timer = timer_read();
  oled_set_start_line(0);
}

void lines_render(void) {
  uint8_t elapsed = timer_elapsed(prompt_timer);
  char current = prompt_buffer[prompt_buffer_line * PROMPT_WIDTH + prompt_cursor];
  if (current != 0) {
    if (elapsed > 5 && prompt_screen_line == 4) {
      if (prompt_scroll == 0) {
        oled_set_cursor(prompt_blink_cursor, prompt_screen_line - 1);
        oled_write_char(' ', false);
        prompt_blink = false;
      }
      prompt_scroll++;
      if (prompt_scroll > 7) {
        prompt_scroll = 0;
        oled_set_start_line(0);
        oled_pan_vertical(false);
        prompt_screen_line = 3;
      } else {
        oled_start_line(prompt_scroll);
      }
      prompt_timer = timer_read();

    } else if (elapsed > 25) {
      if (prompt_blink) {
        oled_set_cursor(prompt_blink_cursor, prompt_screen_line - 1);
        oled_write_char(' ', false);
        prompt_blink = false;
      }
      // write previous char without highlight
      oled_set_cursor(prompt_cursor, prompt_screen_line);
      oled_write_char(current, false);

      prompt_cursor++;
      current = prompt_buffer[prompt_buffer_line * PROMPT_WIDTH + prompt_cursor];
      if (current != 0) {
        // Cursor with char highlighted
        oled_set_cursor(prompt_cursor, prompt_screen_line);
        oled_write_char(current, true);
      } else {
        // EOL
        for (uint8_t i = 0; i < PROMPT_WIDTH; i++) {
          prompt_buffer[prompt_buffer_line * PROMPT_WIDTH + i] = 0;
        }
        prompt_buffer_line++;
        if (prompt_buffer_line == PROMPT_LINES) {
          prompt_buffer_line = 0;
        }

        prompt_blink_cursor = prompt_cursor;

        prompt_cursor = 0;
        prompt_screen_line++;
        oled_set_cursor(prompt_blink_cursor, prompt_screen_line - 1);
        oled_write_char(' ', true);

        prompt_blink = true;
      }
      prompt_timer = timer_read();
    }

  } else if (elapsed > 500) {
    oled_set_cursor(prompt_blink_cursor, prompt_screen_line - 1);
    oled_write_char(' ', prompt_blink);
    prompt_blink = !prompt_blink;
    prompt_timer = timer_read();

  } else if (timer_elapsed(prompt_timeout_timer) > 2000) {
    prompt_info_cursor++;
    if (prompt_info_cursor > INFO_SIZE) {
      prompt_info_cursor = 0;
    }
    switch (prompt_info_cursor) {
      case INFO_WPM:
        prompt_add_f("%d WPM", get_current_wpm());
        break;
      case INFO_LAYERS:
        prompt_add_f("%d layer toggles", prompt_info_layer_activations);
        break;
#ifdef RGB_MATRIX_ENABLE
      case INFO_ANIMATION:
        prompt_add_f("Animation: #%d", rgb_matrix_get_mode());
        break;
      case INFO_SPEED:
        prompt_add_f("speed: %d", rgb_matrix_get_speed());
        break;
      case INFO_HSV:
        prompt_add_f("HSV: %d %d %d", rgb_matrix_get_hue(), rgb_matrix_get_sat(),
            rgb_matrix_get_val());
        break;
#endif
    }
    prompt_timeout_timer = timer_read();
  }
}

void render_mod_status(uint8_t modifiers) {
  /* oled_set_start_line(0); */
  oled_set_cursor(0, 0);
  oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("CTL"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("MOD"), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("A"), false);
#ifdef RGB_MATRIX_ENABLE
  oled_write(dec_to_str(rgb_matrix_get_mode()), false);
  oled_write_P(PSTR("C"), false);
#endif
  /* oled_write_P(crkbd_logo_2, false); */
}

/* #define OLED_MODE_RAIN 0 */
/* #define OLED_MODE_INFO 1 */
/* static uint8_t oled_mode = OLED_MODE_RAIN; */
void oled_task_user(void) {
  /* if (biton32(layer_state) != 0) { */
    /* lines_init(); */
    /* oled_clear(); */
  /* } else { */
    lines_render();
  /* } */
  /* if (biton32(layer_state) == 0) { */
  /* } else { */
    /* uint8_t modifiers = get_mods()|get_oneshot_mods(); */
    /* render_mod_status(modifiers); */
  /* } */
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);
  switch (layer) {
    case 0:
      break;
    case _WM:
      prompt_add_P(PSTR("Xmonad layer active"));
      prompt_timeout_timer = timer_read();
      break;
    case _RA:
      prompt_add_P(PSTR("Raise layer active"));
      prompt_timeout_timer = timer_read();
      break;
    case _AD:
      prompt_add_P(PSTR("Adjust layer active"));
      prompt_timeout_timer = timer_read();
      break;
    default:
      prompt_add_P(PSTR("ERROR unknown layer active"));
      prompt_timeout_timer = timer_read();
      break;
  }
  if (layer != 0) {
    prompt_info_layer_activations++;
  }
  return state;
}

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

