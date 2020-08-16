#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum plaid_layers {
  _QWERTY,
  _XMONAD,
  _RAISE,
  _LOWER,
  _ADJUST
};

enum plaid_keycodes {
  QWERTY = SAFE_RANGE
};

#define XMONAD LM(_XMONAD, MOD_LGUI)
#define SPC_LWR LT(_LOWER, KC_SPACE)
#define ENT_RSE LT(_RAISE, KC_ENT)
#define ADJUST LT(_ADJUST, KC_BSPC)

#define LS_ESC LSFT_T(KC_ESC)
#define RS_QUOT RSFT_T(KC_QUOT)

#define LCT_MINS LCTL_T(KC_MINS)
#define RCT_EQL RCTL_T(KC_EQL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   [  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  ]  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   -  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |LShift|XMONAD| Space/LOWER |RAISE |RShift|ADJUST| RAlt |Bckspc|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_plaid_grid( // Base QWERTY
    KC_LBRC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,
    LS_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RS_QUOT,
    LCT_MINS,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCT_EQL,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSPO, XMONAD,  SPC_LWR, KC_SPC,  ENT_RSE, KC_RSPC, KC_RALT, ADJUST,  KC_RCTL
),

[_XMONAD] = LAYOUT_plaid_grid( // Xmonad with MOD4
    KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_P,    _______,
    KC_LSFT, _______, _______, _______, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
    KC_LSFT, _______, _______, KC_C,    _______, KC_B,    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______
),

[_RAISE] = LAYOUT_plaid_grid( // Raise symbols, arrows, tab and backspace
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_TILD, KC_TAB,  _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_LOWER] = LAYOUT_plaid_grid( // Numbers, Media, F
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, _______,
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_plaid_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, RESET,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF,_______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};


void matrix_init_user(void) {
  eeconfig_init();
}

#ifdef OLED_DRIVER_ENABLE
/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { */
  /* return OLED_ROTATION_0; */
/* } */

/* uint16_t screen_timer = 0; */

void oled_task_user(void) {
  /* oled_clear(); */
  /* for (uint8_t i = 0; i < 15; i++) { */
    /* oled_write_pixel(i * 10, 10, true); */
  /* } */
  oled_write_P(PSTR("                           "), false);
  switch (get_highest_layer(layer_state)) {
    case _RAISE:
      oled_write_ln_P(PSTR(" RAISE"), false);
      break;
    case _LOWER:
      oled_write_ln_P(PSTR(" LOWER"), false);
      break;
    case _XMONAD:
      oled_write_ln_P(PSTR(" XMONAD"), false);
      break;
    case _ADJUST:
      oled_write_ln_P(PSTR(" ADJUST"), false);
      break;
    default: //  for any other layers, or the default layer
      oled_write_ln_P(PSTR(" NULL"), false);
      break;
  }
  oled_write_P(PSTR("      "), false);

  uint8_t modifiers = get_mods();
  if (modifiers & MOD_MASK_SHIFT) {
    oled_write_ln_P(PSTR(" SHIFT"), false);
  } else if (modifiers & MOD_MASK_CTRL) {
    oled_write_ln_P(PSTR(" CONTROL"), false);
  } else if (modifiers & MOD_MASK_ALT) {
    oled_write_ln_P(PSTR(" ALT"), false);
  } else if (modifiers & MOD_MASK_GUI) {
    oled_write_ln_P(PSTR(" MOD4"), false);
  } else {
    oled_write_ln_P(PSTR(" NULL"), false);
  }
  oled_write_P(PSTR("      "), false);
  /* if (timer_elapsed(screen_timer) > 600) { */
    /* prompt = !prompt; */
    /* screen_timer = timer_read(); */
  /* } */
  oled_write_P(PSTR(" PLAID"), false);
  /* oled_scroll_left(); */
}
#endif
