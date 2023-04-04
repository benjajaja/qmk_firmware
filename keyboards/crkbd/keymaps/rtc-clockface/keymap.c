#include "rtc.h"
#include "oled_clockface.h"
#include "pimoroni_trackball.h"
#include "pointing_device.h"

#include QMK_KEYBOARD_H

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
  M_TIME,
  M_RESET,
  PM_SCROLL,
  PM_PRECISION,
  BALL_NCL,
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
#define MOD4 LM(_LOWER, MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.         ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |         |   Y  |   U  |   I  |   O  |   P  |Backsp|
   * |------+------+------+------+------+------|         |------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |         |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|         |------+------+------+------+------+------|
   * |-/LCTR|Z/LGUI|X/LALT|   C  |   V  |   B  |         |   N  |   M  |   ,  |./RALT|//RGUI|=/RCTR|
   * `------+------+------+------+------+------+---. ,---+------+------+------+------+------+------'
   *                          |  Lwr |Shift| Space | |Ent/Rai|Shift|  Enc |
   *                          `--------------------' `--------------------'
   */
  [_BASE] = LAYOUT (
      KC_TAB,      KC_Q,     KC_W,     KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,        KC_P,         KC_BSPC, \
      KC_CAPS,      KC_A,     KC_S,     KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,        KC_SCLN,      KC_QUOT, \
      LCT(KC_MINS),TAT(KC_Z),LGT(KC_X),KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, RGT(KC_DOT), AGT(KC_SLSH), RCT(KC_EQL),\
                                  MOD4, KC_LSPO, KC_SPC,    LT(_RAISE, KC_ENT), KC_RSPC, KC_MUTE \
      ),
  // Numpad, RGB, Reset/wipe, Gimmicks
  [_NUMPAD] = LAYOUT (
      OSL(_FUNC),RGB_RMOD,RGB_HUI,RGB_SAI,RGB_VAI,KC_BRIU,  KC_7,    KC_8,    KC_9,    XXXXXXX, M_TIME, KC_BSPC, \
      RGB_TOG, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,  XXXXXXX, \
      KC_MINS, TO(_FUNC), TO(_PLAIN),M_TIME,M_WIPE,  RESET, KC_1,    KC_2,    KC_3,    KC_0,    KC_COMM, KC_DOT,  \
                                 MOD4,    KC_LSPO, KC_SPC,  KC_ENT,  TG(_NUMPAD), XXXXXXX \
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
                                    XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_MS_BTN1, XXXXXXX \
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
                                 KC_LSFT, TG(_NUMPAD), KC_SPC,      KC_ENT,  XXXXXXX, XXXXXXX \
      ),
  // F1-12
  [_FUNC] = LAYOUT (
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                 XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, TG(_FUNC) \
      ),
};

#ifdef RTC_ENABLE
static uint16_t clock_timeout;
static bool clock_timeout_off = false;
static uint16_t clock_skip_timeout;
static uint8_t rtc_debug[6];
void matrix_init_user(void) { // Runs boot tasks for keyboard
  clock_timeout = timer_read();
  clock_skip_timeout = timer_read();

}
void keyboard_post_init_user(void) {
  char rtc_debug[6] = "NULL ";
  uint8_t eeprom = 0;
  if (readRTCReg(0x37, &eeprom)) {
    snprintf(rtc_debug, sizeof(rtc_debug), "R0%03d", eeprom);
    if (eeprom != 0x1c) {
      snprintf(rtc_debug, sizeof(rtc_debug), "R1%03d", eeprom);
      if (writeRTCReg(0x37, 0x1c)) {
        snprintf(rtc_debug, sizeof(rtc_debug), "W1%03d", eeprom);
        if (readRTCReg(0x37, &eeprom)) {
          snprintf(rtc_debug, sizeof(rtc_debug), "W2%03d", eeprom);
        }
      }
    }
  }
  oled_set_cursor(0, 12);
  oled_write_P(rtc_debug, false);
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

void oled_render_layer_state(void) {
    if (layer_state_is(_BASE)) {
        oled_write_P(PSTR("     "), false);
    } else if (layer_state_is(_NUMPAD)) {
        oled_write_P(PSTR("NUMPD"), false);
    } else if (layer_state_is(_PLAIN)) {
        oled_write_P(PSTR("PLAIN"), false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_P(PSTR("RAISE"), false);
    } else if (layer_state_is(_LOWER)) {
        oled_write_P(PSTR("LOWER"), false);
    } else if (layer_state_is(_FUNC)) {
        oled_write_P(PSTR("FUNCT"), false);
    }
}


#ifdef RTC_ENABLE
static bool time_mode_on = false;
static uint8_t time_field[2] = {0,0};
enum time_cursor_fields {
  TIMECUR_YEAR,
  TIMECUR_MONTH,
  TIMECUR_DAY,
  TIMECUR_WEEKDAY,
  TIMECUR_HOUR,
  TIMECUR_MINUTE,
  TIMECUR_SECOND,
};
static uint8_t time_cursor_field = TIMECUR_YEAR;
static uint8_t time_cursor_digit = 0;

void oled_render_time(void) {
  /* if (timer_elapsed(clock_skip_timeout) < 500) { */
    /* oled_set_cursor(0, 12); */
    /* return; */
  /* } */
  /* clock_skip_timeout = timer_read(); */

  static uint8_t second;
  static uint8_t minute;
  static uint8_t hour;
  static uint8_t dayOfWeek;
  static uint8_t dayOfMonth;
  static uint8_t month;
  static uint8_t year;
  static uint8_t last_second = 60;
  static bool half_step = true;

  if (readRTCtime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year)) {

    static bool render_clockface = false;
    if (half_step && second != last_second) {
      last_second = second;
      half_step = false;
      clock_skip_timeout = timer_read();
      render_clockface = true;

    } else if (!half_step && timer_elapsed(clock_skip_timeout) > 500) {
      half_step = true;
      render_clockface = true;
    }
    if (render_clockface) {
      render_clockface = false;
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_render_face();
      oled_render_hand_second(second, half_step);
      oled_render_hand_minute(minute);
      oled_render_hand_hour((hour % 12) * 5 + (minute / 12));
    }

    oled_set_cursor(0, 4);


    if (!clock_timeout_off) {

      if (time_mode_on) {
        switch (time_cursor_field) {
          case TIMECUR_SECOND:
            oled_write_P(PSTR("Sec"), false);
            break;
          case TIMECUR_MINUTE:
            oled_write_P(PSTR("Min"), false);
            break;
          case TIMECUR_HOUR:
            oled_write_P(PSTR("Hou"), false);
            break;
          case TIMECUR_DAY:
            oled_write_P(PSTR("Day"), false);
            break;
          case TIMECUR_WEEKDAY:
            oled_write_P(PSTR("Wkd"), false);
            break;
          case TIMECUR_MONTH:
            oled_write_P(PSTR("Mon"), false);
            break;
          case TIMECUR_YEAR:
            oled_write_P(PSTR("Yea"), false);
            break;
          default:
            oled_write_P(PSTR("???"), false);
            break;
        }
        static char set_value[4] = {};
        snprintf(set_value, sizeof(set_value), "%1d", time_field[0]);
        oled_write(set_value, true);
        snprintf(set_value, sizeof(set_value), "%1d", time_field[1]);
        oled_write(set_value, true);
      } else {
        oled_write_P(PSTR("     "), false);
      }

      static char time_str[8] = {};
      snprintf(time_str, sizeof(time_str), "%02d:%02d", hour, minute);
      oled_write(time_str, false);


      static char sec_str[8] = {};
      snprintf(sec_str, sizeof(sec_str), half_step ? "   %02d" : "  :%02d", second);
      oled_write(sec_str, false);

      oled_write_P(PSTR("     "), false);

      switch (dayOfWeek) {
        case 1:
          oled_write_P(PSTR(" Mon "), false); break;
        case 2:
          oled_write_P(PSTR(" Tue "), false); break;
        case 3:
          oled_write_P(PSTR(" Wed "), false); break;
        case 4:
          oled_write_P(PSTR(" Thu "), false); break;
        case 5:
          oled_write_P(PSTR(" Fri "), false); break;
        case 6:
          oled_write_P(PSTR(" Sat "), false); break;
        default:
          oled_write_P(PSTR(" Sun "), false); break;
      }

      oled_write_P(PSTR("     "), false);

      static char date_daymonth[8] = {};
      snprintf(date_daymonth, sizeof(date_daymonth), "%02d/%02d", dayOfMonth, month);
      oled_write(date_daymonth, false);

      static char date_year[8] = {};
      snprintf(date_year, sizeof(date_year), " %04d", 2000 + year);
      oled_write(date_year, false);

    }
    oled_set_cursor(0, 12);

  } else {
    oled_write_P(PSTR("CLOCK"), false);
    oled_write_P(PSTR("ERROR"), false);
    oled_scroll_right();
    oled_set_cursor(0, 12);
  }

}
#endif

void oled_task_user(void) {
#ifdef RTC_ENABLE
  oled_render_time();

  if (!clock_timeout_off) {
    if (timer_elapsed(clock_timeout) > OLED_CLOCK_TIMEOUT) {
      clock_timeout_off = true;
      oled_set_cursor(0, 4);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      rtc_debug[0] = 0;
    } else {
      oled_render_layer_state();
    }
  }
#endif
}

#ifdef RTC_ENABLE
void mode_set_time_toggle(void) {
  time_mode_on = !time_mode_on;
  if (time_mode_on) {
    time_cursor_field = TIMECUR_HOUR;
    time_cursor_digit = 0;
    /* writeRTCosf(); */
  }
}

void mode_set_time_add(uint8_t num) {
  time_field[time_cursor_digit] = num;
  time_cursor_digit += 1;
  if (time_cursor_digit >= 2) {

    uint8_t value = time_field[0] * 10 + time_field[1];
    if (!writeRTCtime_field(time_cursor_field, value)) {
      time_mode_on = false;
      return;
    }

    if (time_cursor_field == TIMECUR_WEEKDAY) {
      time_mode_on = false;
      return;
    }

    time_cursor_field += 1;
    if (time_cursor_field > TIMECUR_SECOND) {
      time_cursor_field = TIMECUR_YEAR;
    }
    time_cursor_digit = 0;
    time_field[0] = 0;
    time_field[1] = 0;
  }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RTC_ENABLE
  if (record->event.pressed) {
    clock_timeout = timer_read();
    clock_timeout_off = false;
  }
#endif

  switch (keycode) {
#ifdef RTC_ENABLE
    case M_TIME:
      if (record->event.pressed) {
        mode_set_time_toggle();
      }
      break;
#endif
    case M_RESET:
      if (record->event.pressed) {
#ifdef PIMORONI_TRACKBALL_ENABLE
        trackball_set_rgbw(RGB_GREEN, 0x44);
#endif
        reset_keyboard();
      }
      break;
#ifdef PIMORONI_TRACKBALL_ENABLE
    case PM_SCROLL:
        trackball_set_scrolling(record->event.pressed);
        /* run_trackball_cleanup(); */
        break;
    case PM_PRECISION:
        if (record->event.pressed) {
            trackball_set_precision(1.5);
        } else {
            trackball_set_precision(1);
        }
        /* run_trackball_cleanup(); */
        break;
#if !defined(MOUSEKEY_ENABLE)
    case KC_MS_BTN1:
        mouse_button_one = record->event.pressed;
        trackball_register_button(mouse_button_one | trackball_button_one, MOUSE_BTN1);
        break;
    case KC_MS_BTN2:
        trackball_register_button(record->event.pressed, MOUSE_BTN2);
        break;
    case KC_MS_BTN3:
        trackball_register_button(record->event.pressed, MOUSE_BTN3);
        break;
#    endif
#endif
  }

#ifdef RTC_ENABLE
  if (time_mode_on && record->event.pressed && keycode >= 30 && keycode < 40) {
    if (keycode == 39) {
      mode_set_time_add(0);
    } else {
      mode_set_time_add(keycode - 29);
    }
  }
#endif
  return true;
}

#endif // OLED_DRIVER_ENABLE

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    if (layer_state_is(_BASE)) {
      tap_code(KC_MS_WH_DOWN);
    } else if (layer_state_is(_RAISE)) {
      tap_code(KC_VOLU);
    } else if (layer_state_is(_NUMPAD)) {
      tap_code(KC_BRIU);
    }
  } else {
    if (layer_state_is(_BASE)) {
      tap_code(KC_MS_WH_UP);
    } else if (layer_state_is(_RAISE)) {
      tap_code(KC_VOLD);
    } else if (layer_state_is(_NUMPAD)) {
      tap_code(KC_BRID);
    }
  }
  DRV_pulse(26);
}
#endif

#ifdef PIMORONI_TRACKBALL_ENABLE
void keyboard_post_init_keymap(void) {
    trackball_set_precision(1.0);
    /* trackball_set_rgbw(RGB_RED, 0x00); */
}
void shutdown_keymap(void) {
    trackball_set_rgbw(RGB_WHITE, 0xFF);
}

static bool mouse_button_one, trackball_button_one;

void trackball_check_click(bool pressed, report_mouse_t* mouse) {
    if (mouse_button_one | pressed) {
        mouse->buttons |= MOUSE_BTN1;
    } else {
        mouse->buttons &= ~MOUSE_BTN1;
    }
    trackball_button_one = pressed;
    trackball_set_rgbw(RGB_WHITE, 0xFF);
    DRV_pulse(4);
}
#endif

#ifdef PIMORONI_TRACKBALL_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        trackball_set_rgbw(RGB_PINK, 0x00);
        DRV_pulse(7);
        break;
    case _LOWER:
        trackball_set_rgbw(RGB_MAGENTA, 0x88);
        DRV_pulse(4);
        break;
    case _NUMPAD:
        trackball_set_rgbw(RGB_GREEN, 0x00);
        DRV_pulse(12);
        break;
    default:
        trackball_set_rgbw(RGB_PURPLE, 0x00);
        DRV_pulse(24);
        break;
    }
    return state;
}
#endif
