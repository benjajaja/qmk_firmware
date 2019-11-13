#include QMK_KEYBOARD_H
#include "prompt.h"

extern keymap_config_t keymap_config;
extern uint8_t         is_master;
extern uint16_t prompt_clock_timer;
extern char prompt_clock_user_hours;
extern char prompt_clock_user_minutes;
extern char prompt_clock_user_seconds;

// Layers
#define _BASE 0
#define _NUMPAD 1
#define _PLAIN 2
#define _RAISE 3
#define _LOWER 4
#define _FUNC 5

enum custom_keycodes {
  MODDH  = SAFE_RANGE,
  M_WIPE,
  M_RAN64,
  M_PROMPT,
};

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
#define MOD4 LM(_LOWER, MOD_LGUI)

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
  [_BASE] = LAYOUT (
      KC_TAB,      KC_Q,     KC_W,     KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,        KC_P,         KC_BSPC, \
      KC_ESC,      KC_A,     KC_S,     KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,        KC_SCLN,      KC_QUOT, \
      LCT(KC_MINS),TAT(KC_Z),LGT(KC_X),KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, RGT(KC_DOT), AGT(KC_SLSH), RCT(KC_EQL),\
                                  MOD4, KC_LSPO, KC_SPC,    LT(_RAISE, KC_ENT), KC_RSPC, TG(_NUMPAD) \
      ),
  // Numpad, RGB, Reset/wipe, Gimmicks
  [_NUMPAD] = LAYOUT (
      OSL(_FUNC),RGB_RMOD,RGB_HUI,RGB_SAI,RGB_VAI,KC_BRIU,  KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX, KC_BSPC, \
      RGB_TOG, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,  XXXXXXX, \
      KC_MINS, TO(_FUNC), TO(_PLAIN),M_PROMPT,M_WIPE,  RESET, KC_1,    KC_2,    KC_3,    KC_0,    KC_COMM, KC_DOT,  \
                                 MOD4,    KC_LSPO, KC_SPC,  KC_ENT,  KC_RSPC, TG(_NUMPAD) \
      ),
  // No modtaps, for games and such
  [_PLAIN] = LAYOUT (
      KC_TAB,      KC_Q,     KC_W,     KC_E, KC_R, KC_T,            KC_Y, KC_U, KC_I,    KC_O,        KC_P,         KC_BSPC, \
      KC_ESC,      KC_A,     KC_S,     KC_D, KC_F, KC_G,            KC_H, KC_J, KC_K,    KC_L,        KC_SCLN,      KC_QUOT, \
      KC_LCTRL,    KC_Z,     KC_X,     KC_C, KC_V, KC_B,            KC_N, KC_M, KC_COMM, RGT(KC_DOT), AGT(KC_SLSH), RCT(KC_EQL),\
                                  MO(_RAISE),KC_LSFT,KC_SPC,          KC_ENT, KC_RSFT, TO(_BASE) \
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
  [_RAISE] = LAYOUT (
      KC_TILD, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS, \
      KC_GRV,  KC_LCBR, KC_PGUP,KC_PGDN, KC_END,  KC_HOME,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCBR, KC_PIPE, \
      KC_LBRC, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RBRC, \
                                    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX \
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
  [_LOWER] = LAYOUT (
      KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_P,    XXXXXXX, \
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_T,        KC_H,    KC_J,    KC_K,    KC_L,    XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, KC_C,    XXXXXXX, KC_B,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                 KC_LSFT, TO(_NUMPAD), KC_SPC,      KC_ENT,  XXXXXXX, XXXXXXX \
      ),
  // F1-12
  [_FUNC] = LAYOUT (
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                 XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, TG(_FUNC) \
      ),
};

void keyboard_post_init_user(void) {
  /* debug_enable=true; */
}

void matrix_init_user(void) { // Runs boot tasks for keyboard
#ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_config.mode;
#endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  iota_gfx_init(!has_usb());   // turns on the display
#endif
  const uint8_t layer_count = sizeof(keymaps) / sizeof(keymaps[0]);
  prompt_init(layer_count);
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;
  } else {
    return OLED_ROTATION_270;
  }
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    render_space();
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
        render_space();
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
        render_space();
    } else if(layer_state_is(_FUNC)) {
        oled_write_P(raise_layer, false);
        oled_write_P(PSTR("FUNCT"), false);
    } else if(layer_state_is(_PLAIN)) {
        oled_write_P(default_layer, false);
        oled_write_P(PSTR("PLAIN"), false);
    } else if(layer_state_is(_NUMPAD)) {
        oled_write_P(adjust_layer, false);
        render_space();
    } else {
        oled_write_P(default_layer, false);
        render_space();
    }
}

static uint32_t clock_seconds = 0;
static uint32_t clock_minutes = 0;
static uint32_t clock_hours = 0;
void render_time(void) {
  clock_seconds = timer_elapsed32(prompt_clock_timer) / 1000;
  clock_minutes = clock_seconds / 60;
  clock_hours = clock_minutes / 60;
  static char clock_buffer[5];
  sprintf(
      clock_buffer,
      "%02lu:%02lu",
      (clock_hours + prompt_clock_user_hours) % 24,
      (clock_minutes + prompt_clock_user_minutes) % 60
  );
  oled_write(clock_buffer, false);
}

void render_status_main(void) {
    render_logo();
    /* render_time(); */
    oled_write_P(PSTR("corne"), false);
    render_space();
    render_layer_state();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}


void oled_task_user(void) {
  if (is_prompt_half) {
    prompt_render();
  } else {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);
  if (is_prompt_half && prompt_command == 0) {
    switch (layer) {
      case 0:
        prompt_add_P(PSTR("base layer active"));
        prompt_timeout_reset();
        break;
      case _LOWER:
        prompt_add_P(PSTR("xmonad layer active"));
        prompt_timeout_reset();
        break;
      case _RAISE:
        prompt_add_P(PSTR("raised layer active"));
        prompt_timeout_reset();
        break;
      case _NUMPAD:
        prompt_add_P(PSTR("system layer active"));
        prompt_timeout_reset();
        break;
      case _FUNC:
        prompt_add_P(PSTR("fn layer active"));
        prompt_timeout_reset();
        break;
      case _PLAIN:
        prompt_add_P(PSTR("vanilla layer active"));
        prompt_timeout_reset();
        break;
      default:
        prompt_add_P(PSTR("unknown layer active"));
        prompt_timeout_reset();
        break;
    }
  }
  if (layer != 0) {
    prompt_info_layer_activations++;
  }
  prompt_timeout_reset();
  return state;
}

void suspend_power_down_keymap(void) {
  oled_off();
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_keymap(void) {
  oled_on();
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_set_suspend_state(false);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (is_prompt_half && prompt_command != 0) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
      keycode = keycode & 0xFF;
    }
    switch (keycode) {
      case KC_ENT:
        if (record->event.pressed) {
          process_prompt_command();
          layer_state_set(1U << _BASE);
        }
        return false;
        break;
      default:
        if (record->event.pressed) {
          prompt_add_char(keycode, get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)));
        }
        return false;
        break;
    }
  }
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
    case M_PROMPT:
      if (record->event.pressed) {
        prompt_start_command();
        layer_state_set(1U << _PLAIN);
      }
      return false;
      break;
  }
  return true;
};

