#include QMK_KEYBOARD_H
#include QMK_KEYBOARD_H
#include "rgblight.h"
#include <print.h>

#ifndef KC_LOCK
#define KC_LOCK KC_NO
#endif

enum keyboard_layers {
  _BL = 0, // Base Layer
  _SL,     // Normal-Space Layer
  _FL,     // Function Layer
  _CL,     // Control Layer
};

enum unicode_names {
  SQUID,
};

const uint32_t PROGMEM unicode_map[] = {
  [SQUID]  = 0x01F991, // 🦑
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT_60_tsangan(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_ESC,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, _______,
		KC_LGUI, KC_LCTL,          KC_LALT,                   LT(_FL,KC_SPC),                              KC_RGUI,          TO(_SL),KC_RCTL
	),
	[_SL] = LAYOUT_60_tsangan(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
		_______, _______,          _______,                   KC_SPACE,                                    _______,          MO(_FL), _______
	),
	[_FL] = LAYOUT_60_tsangan(
		DEBUG, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_HOME,
		RESET,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_END,
		KC_LOCK,          _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
		_______, _______,          _______,                   TO(_CL),                                     _______,          _______, _______
	),
	[_CL] = LAYOUT_60_tsangan(
		RGB_MODE_PLAIN, RGB_MODE_KNIGHT, RGB_MODE_SNAKE, RGB_MODE_BREATHE, RGB_MODE_GRADIENT, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
		RESET,            RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
		_______,          BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, _______, _______, _______, _______, _______, _______, _______, _______,
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
		_______, _______,          _______,                   _______,                                     _______,          TG(_CL), _______
	)
};

/**
 * Terminal Prompt
 * Mimicks a terminal prompt. On keystrokes, the led bar is filled. Backspace
 * removes from bar. Enter clears bar. After some timeout, the bar is also cleared.
 * A blinking cursor is displayed at the right of the bar.
 * This can't be defined as an animation, because animations only are called on an
 * interval, not on keypress. In the future all animations could be enhanced to
 * react to keystrokes in QMK.
 */

uint64_t bits = 0; // desired state
uint8_t phosphors[LEDS_REAL]; // decaying state
uint8_t cursor_pos = 0;

uint16_t interval_time = 10; // maybe too short...
uint16_t reset_time = 5000;
uint16_t last_timer = 0;
uint16_t timer_pos = 0;
uint16_t reset_timer = 0;

void setled(uint8_t h, uint8_t s, uint8_t v, uint8_t i);
void setled_range(uint8_t h, uint8_t s, uint8_t v, uint8_t f, uint8_t t);
void reset_chars(void);
void add_char(bool space);
void remove_char(void);
void animate_phosphor(void);

void keyboard_pre_init_user(void) {
  for (uint8_t i = 0; i < LEDS_REAL; i++) {
    phosphors[i] = 0;
  }
  // reset the bar and animation
  rgblight_set_effect_range(LEDS_UNUSED, LEDS_REAL);
  rgblight_mode(RGBLIGHT_MODE_KNIGHT);
  for (uint8_t i = 0; i < LEDS_REAL; i++) {
      setled(rgblight_get_hue(), 0, 0, i);
  }
}

void keyboard_post_init_user(void) {
  setled(0, 0, 0, LED_LAYER); // clear layer LED
  reset_timer = last_timer = timer_read();
  dprintf("Terminal animation: %u bits\n", (sizeof (bits)) * 8);
  for (uint8_t i = 0; i < LEDS_REAL; i++) {
    add_char(false);
  }
}



// animate, like the built-in animations, with timer_* functions
void matrix_scan_user(void) {
  if (timer_elapsed(reset_timer) > reset_time) {
      reset_chars();
      reset_timer = timer_read();
      return;
  }
  if (timer_elapsed(last_timer) < interval_time) {
    return;
  }
  last_timer += interval_time;
  timer_pos += 4;
  if (timer_pos >= 255) {
    timer_pos = 0;
    last_timer = timer_read();
  }
  animate_phosphor();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // substract modifier keys
  // TODO: deal with Ctrl-C etc?
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  switch (keycode) {
    case KC_A ... KC_Z:
    case KC_1 ... KC_0:
    case KC_LBRC:
    case KC_RBRC:
    case KC_SCLN:
    case KC_QUOT:
    case KC_COMM:
    case KC_DOT:
    case KC_SLSH:
    case KC_BSLS:
      if (record->event.pressed) {
        add_char(false);
      }
      break;
    case KC_ENTER:
    case KC_ESC:
      if (record->event.pressed) {
        reset_chars();
      }
      break;
    case KC_BSPC:
      if (record->event.pressed) {
        remove_char();
      }
      break;
    case KC_SPACE:
      if (record->event.pressed) {
        add_char(true);
      }
      break;
  }
  reset_timer = timer_read();
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _SL:
      rgblight_set_effect_range(LEDS_UNUSED, LEDS_REAL - 1);
      setled(RGB_AZURE, LEDS_REAL - 1);
      break;
  case _FL:
      rgblight_set_effect_range(LEDS_UNUSED, LEDS_REAL - 1);
      setled(HSV_CYAN, LEDS_REAL - 1);
      break;
  case _CL:
      rgblight_set_effect_range(LEDS_UNUSED, LEDS_REAL - 1);
      setled(HSV_RED, LEDS_REAL - 1);
      break;
  case _BL:
  default:
      rgblight_set_effect_range(LEDS_UNUSED, LEDS_REAL);
      setled(0, 0, 0, LEDS_REAL - 1);
      break;
  }
  return state;
}

void setled(uint8_t h, uint8_t s, uint8_t v, uint8_t i) {
  uint16_t modulated = v * rgblight_get_val() / 255;
  rgblight_sethsv_at(h, s, modulated, LEDS_UNUSED + i);
}

void setled_range(uint8_t h, uint8_t s, uint8_t v, uint8_t f, uint8_t t) {
  uint16_t modulated = v * rgblight_get_val() / 255;
  rgblight_sethsv_range(h, s, modulated, LEDS_UNUSED + f, LEDS_UNUSED + t + 1);
}

void reset_chars(void) {
  bits = 0;
  phosphors[cursor_pos] = timer_pos;
  cursor_pos = 0;
}

void add_char(bool space) {
  if (cursor_pos == LEDS_REAL - 1) {
    // like a carriage return
    reset_chars();
    return;
  }

  if (!space) {
    // set bit at cursor
    bits = bits | ((uint64_t)1 << cursor_pos);
  }
  phosphors[cursor_pos] = timer_pos;
  cursor_pos += 1;
}

void remove_char(void) {
  if (cursor_pos == 0) return;

  // unset bit behind cursor
  bits = bits & ~((uint64_t)1 << (cursor_pos - 1));

  phosphors[cursor_pos] = timer_pos;
  cursor_pos -= 1;
}

void animate_phosphor() {
  uint16_t value = fmax(0, fmin(255,
      timer_pos < 32
        ? (timer_pos * timer_pos / 2)
        : 255 - timer_pos
      ));
  setled(rgblight_get_hue(), value, value, cursor_pos);

  for (uint8_t i = 0; i < LEDS_REAL; i++) {
    if (i == cursor_pos) {
      continue;
    }

    if (((bits >> i) & (uint64_t)1) == 1) {
      if (phosphors[i] != 255) {
        phosphors[i] = fmin(255, phosphors[i] + CHAR_DECAY);
        setled(rgblight_get_hue(), phosphors[i], phosphors[i], i);
      }
    } else {
      if (phosphors[i] != 0) {
        phosphors[i] = fmax(0, phosphors[i] - CHAR_DECAY);
        setled(rgblight_get_hue(), phosphors[i], phosphors[i], i);
      }
    }
  }
}

