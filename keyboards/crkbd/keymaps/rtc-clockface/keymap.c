#include "rtc.h"
#include "oled_clockface.h"

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
      KC_MINS, TO(_FUNC), TO(_PLAIN),M_TIME,M_WIPE,  RESET, KC_1,    KC_2,    KC_3,    KC_0,    KC_COMM, KC_DOT,  \
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

static uint16_t clock_timeout;
static bool clock_timeout_off = false;
void matrix_init_user(void) { // Runs boot tasks for keyboard
  clock_timeout = timer_read();
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
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

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}



void oled_render_time(void) {
  static uint8_t second;
  static uint8_t minute;
  static uint8_t hour;
  static uint8_t dayOfWeek;
  static uint8_t dayOfMonth;
  static uint8_t month;
  static uint8_t year;
  static uint8_t last_second = 60;
  if (readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year)) {

    if (second != last_second) {
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_write_P(PSTR("     "), false);
      oled_render_face();
      oled_render_hand_second(second, false);
      oled_render_hand_minute(minute);
      oled_render_hand_hour((hour % 12) * 5 + minute);

      oled_set_cursor(0, 5);


      if (!clock_timeout_off) {
        static char time_str[8] = {};
        snprintf(time_str, sizeof(time_str), "%02d:%02d", hour, minute);
        oled_write(time_str, time_mode_on);

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

        static char date_daymonth[8] = {};
        snprintf(date_daymonth, sizeof(date_daymonth), "%02d/%02d", dayOfMonth, month);
        oled_write(date_daymonth, false);

        static char date_year[8] = {};
        snprintf(date_year, sizeof(date_year), "/%04d", year + 2000);
        oled_write(date_year, false);

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
      }
    }

    last_second = second;

  } else {
    oled_write_P(PSTR(" ERR "), false);
    oled_write_P(PSTR(" ERR "), false);
  }
  oled_set_cursor(0, 10);

  /* static uint8_t tem_int; */
  /* static uint8_t tem_frac; */
  /* static char temp_str[10] = {}; */
  /* if (readDS3231temp(&tem_int, &tem_frac)) { */
    /* snprintf(temp_str, sizeof(temp_str), "%02d.%01dC", tem_int, tem_frac); */
    /* oled_write(temp_str, false); */
  /* } else { */
    /* oled_write_P(PSTR(" ERR "), false); */
  /* } */
}

void oled_task_user(void) {
  if (is_master) {
    oled_render_time();

    if (!clock_timeout_off) {
      if (timer_elapsed(clock_timeout) > 10000) {
        clock_timeout_off = true;
        oled_set_cursor(0, 5);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR("     "), false);
      } else {
        oled_render_layer_state();
      }
    }

  } else {
    oled_render_logo();
  }
}

/* const uint8_t TIMECUR_LENGTHS[] = { */
  /* [TIMECUR_HOUR] = 2, */
  /* [TIMECUR_MINUTE] = 2, */
  /* [TIMECUR_SECOND] = 2, */
/* }; */
void mode_set_time_toggle(void) {
  time_mode_on = !time_mode_on;
  if (time_mode_on) {
    time_cursor_field = TIMECUR_HOUR;
    time_cursor_digit = 0;
  }
}

void mode_set_time_add(uint8_t num) {
  time_field[time_cursor_digit] = num;
  time_cursor_digit += 1;
  if (time_cursor_digit >= 2) {

    uint8_t value = time_field[0] * 10 + time_field[1];
    if (!writeDS3231time_field(time_cursor_field, value)) {
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    clock_timeout = timer_read();
    clock_timeout_off = false;
    oled_on();
  }
  switch (keycode) {
    case M_TIME:
      if (record->event.pressed) {
        mode_set_time_toggle();
      }
      break;
  }
  if (time_mode_on && record->event.pressed && keycode >= 30 && keycode < 40) {
    if (keycode == 39) {
      mode_set_time_add(0);
    } else {
      mode_set_time_add(keycode - 29);
    }
  }
  return true;
}

#endif // OLED_DRIVER_ENABLE
