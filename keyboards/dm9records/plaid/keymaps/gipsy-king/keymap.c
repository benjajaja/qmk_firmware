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
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSPO, XMONAD,  SPC_LWR, KC_SPC,  ENT_RSE, KC_RSPC, KC_RALT, ADJUST,  KC_BSPC
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

#define BLINKEN_RANDOM_STARTLE false
static uint16_t blinken_timer = 0;
static uint16_t next_timeout = 1000;
enum blinken_modes {
  BLINK_HOLD,
  BLINK_STARTLED,
  BLINK_STARTLED_LAYER
};
static uint16_t blinken_mode = BLINK_HOLD;
static uint16_t blinken_timer_startled = 0;
static uint16_t blinken_startled_state = 0;

void keyboard_post_init_user(void) {
  writePinHigh(LED_RED);
  writePinHigh(LED_GREEN);
  blinken_timer = timer_read();
}

void matrix_scan_user(void) {
  if (blinken_mode != BLINK_STARTLED_LAYER && timer_elapsed(blinken_timer) > next_timeout) {
    blinken_timer = timer_read();
    if (BLINKEN_RANDOM_STARTLE && rand() % 5 == 0) {
      blinken_mode = BLINK_STARTLED;
      blinken_timer_startled = timer_read();
      blinken_startled_state = 0;
    } else {
      blinken_mode = BLINK_HOLD;

      if(rand() % 2 == 0) {
        next_timeout = 1000;
      } else if(rand() % 2 == 0) {
        next_timeout = 500;
      } else {
        next_timeout = 300;
      }

      if(rand() % 2 == 0) {
        writePinLow(LED_RED);
      } else {
        writePinHigh(LED_RED);
      }
      if(rand() % 2 == 0) {
        writePinLow(LED_GREEN);
      } else {
        writePinHigh(LED_GREEN);
      }
    }
  } else if ((blinken_mode == BLINK_STARTLED || blinken_mode == BLINK_STARTLED_LAYER)
      && timer_elapsed(blinken_timer_startled) > 50) {
      blinken_timer_startled = timer_read();
      switch (blinken_startled_state) {
        case 0:
          writePinLow(LED_GREEN);
          blinken_startled_state += 1;
          break;
        case 1:
          writePinHigh(LED_RED);
          blinken_startled_state += 1;
          break;
        case 2:
          writePinHigh(LED_GREEN);
          blinken_startled_state += 1;
          break;
        case 3:
          writePinLow(LED_RED);
          blinken_startled_state = 0;
          break;
      }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _RAISE:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  case _XMONAD:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  case _LOWER:
      blinken_mode = BLINK_STARTLED_LAYER;
      break;
  default:
      blinken_mode = BLINK_HOLD;
      break;
  }
  return state;
}
