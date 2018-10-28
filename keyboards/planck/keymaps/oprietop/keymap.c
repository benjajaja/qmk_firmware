/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Allow printing version info
#include "version.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNCT,
  _ADJUST
};

enum planck_keycodes {
  // Layers
  QWERTY = SAFE_RANGE,
  COLEMAK,
  // Macros
  KC_VER,
  KC_PULL,
  KC_PUSH,
  KC_LS,
  KC_INCL,
  // Sound
  S_BSKTC,
  S_ODEJY,
  S_RCKBY,
  S_DOEDR,
  S_SCALE,
  S_ONEUP,
  S_COIN,
  S_SONIC,
  S_ZELDA,
  S_DOOM
};

#ifdef AUDIO_ENABLE
  float song_basketcase[][2] = SONG(BASKET_CASE);
  float song_ode_to_joy[][2] = SONG(ODE_TO_JOY);
  float song_rock_a_bye_baby[][2] = SONG(ROCK_A_BYE_BABY);
  float song_doe_a_deer[][2] = SONG(DOE_A_DEER);
  float song_scale[][2] = SONG(MUSIC_SCALE_SOUND);
  float song_coin[][2] = SONG(COIN_SOUND);
  float song_one_up[][2] = SONG(ONE_UP_SOUND);
  float song_sonic_ring[][2] = SONG(SONIC_RING);
  float song_zelda_puzzle[][2] = SONG(ZELDA_PUZZLE);
  float song_doom[][2] = SONG(E1M1_DOOM);
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// MOmentary layer switch
#define ADJUST MO(_ADJUST)

#define RALSPC RALT_T(KC_SPC)

// Layer Tap. Switch to <left> layer when held of tap <right>
#define LOSPC LT(_LOWER, KC_BSPC)
#define RAENT LT(_RAISE, KC_ENT)
#define DELFN LT(_FUNCT, KC_DEL)

// Shift when held, Enter when tapped
#define LSENT LSFT_T(KC_ENT)
#define RSENT RSFT_T(KC_ENT)

// Cut/Paste shortcuts
#define KC_CPY LCTL(KC_INS)
#define KC_CUT LSFT(KC_DEL)
#define KC_PST RSFT(KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Lower | FN   |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LGUI, KC_LALT, DELFN,   LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Lower | FN   |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    LSENT,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RSENT,
    KC_LCTL, KC_LGUI, KC_LALT, DELFN,   LOWER,   RALSPC,  RSENT,   RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_FUNCT] = LAYOUT_planck_grid(
    S_BSKTC, S_ODEJY, S_RCKBY, _______, KC_PST,  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN3, KC_WH_U, KC_BTN4,
    S_DOEDR, S_SCALE, S_ONEUP, _______, KC_CUT,  _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R,
    S_COIN,  S_SONIC, S_ZELDA, S_DOOM,  KC_CPY,  KC_INCL, KC_PULL, KC_PUSH, KC_LS,   KC_BTN1, KC_MS_U, KC_BTN2,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   KC_VER,  _______, _______, _______, _______, _______,  _______, _______, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Layers
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    // Macros
    case KC_INCL:
      SEND_STRING("#include <>"SS_TAP(X_LEFT));
      return false;
      break;
    case KC_PULL:
      SEND_STRING("git pull"SS_TAP(X_ENTER));
      return false;
      break;
    case KC_PUSH:
      SEND_STRING("git push"SS_TAP(X_ENTER));
      return false;
      break;
    case KC_LS: 
      SEND_STRING("ls -la"SS_TAP(X_ENTER));
      return false;
      break;
    case KC_VER:
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION "@" QMK_BUILDDATE);
      return false;
      break;
    // Sound
    case S_BSKTC:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_basketcase);
      }
      return false;
      break;
    case S_ODEJY:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_ode_to_joy);
      }
      return false;
      break;
    case S_RCKBY:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_rock_a_bye_baby);
      }
      return false;
      break;
    case S_DOEDR:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_doe_a_deer);
      }
      return false;
      break;
    case S_SCALE:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_scale);
      }
      return false;
      break;
    case S_ONEUP:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_one_up);
      }
      return false;
      break;
    case S_COIN:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_coin);
      }
      return false;
      break;
    case S_SONIC:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_sonic_ring);
      }
      return false;
      break;
    case S_ZELDA:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_zelda_puzzle);
      }
      return false;
      break;
    case S_DOOM:
      if (record->event.pressed) {
          stop_all_notes();
          PLAY_SONG(song_doom);
      }
      return false;
      break;
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
