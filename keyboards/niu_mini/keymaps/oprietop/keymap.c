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
 :* You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _COLEMAK,
  _COLEMDH,
  _DVORAK,
  _LOWER,
  _RAISE,
  _FUNCT,
  _ADJUST,
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  COLEMDH,
  DVORAK,
};

// MOmentary layer switch
#define ADJUST MO(_ADJUST)

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
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  KC_LCTL, KC_LALT, KC_LGUI, DELFN, LOSPC, KC_SPC, KC_SPC, RAENT, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_F,  KC_P,  KC_G,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_R,    KC_S,  KC_T,  KC_D,   KC_H,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,   KC_K,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  KC_LCTL, KC_LALT, KC_LGUI, DELFN, LOSPC, KC_SPC, KC_SPC, RAENT, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT, KC_P,  KC_Y,   KC_F,   KC_G,  KC_C,    KC_R,    KC_L,    KC_BSPC,
  KC_ESC,  KC_A,    KC_O,    KC_E,   KC_U,  KC_I,   KC_D,   KC_H,  KC_T,    KC_N,    KC_S,    KC_SLSH,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,   KC_K,  KC_X,   KC_B,   KC_M,  KC_W,    KC_V,    KC_Z,    KC_ENT ,
  KC_LCTL, KC_LALT, KC_LGUI, DELFN,  LOSPC, KC_SPC, KC_SPC, RAENT, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Colemak DH
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SEnt |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |  Up  | SEnt |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |DelFN |Lower |    Space    |Raise |   /  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMDH] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_Q,    KC_W,    KC_F,  KC_P,  KC_B,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_TAB,  KC_A,    KC_R,    KC_S,  KC_T,  KC_G,   KC_M,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
  LSENT,   KC_Z,    KC_X,    KC_C,  KC_D,  KC_V,   KC_K,   KC_H,  KC_COMM, KC_DOT,  KC_UP,   RSENT,
  KC_LCTL, KC_LALT, KC_LGUI, DELFN, LOSPC, KC_SPC, KC_SPC, RAENT, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Del  |Pg Up |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Ins  | Home |Pg Dn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, _______,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_DEL,  KC_PGUP, _______,
  _______, _______, _______, _______, _______, _______, _______, ADJUST,     KC_INS,     KC_HOME, KC_PGDN, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_DEL,  KC_PGUP, _______,
  _______, _______, _______, _______, ADJUST, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_FUNCT] = LAYOUT_ortho_4x12(
  _______, _______, _______, _______, KC_PST,  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN3, KC_WH_U, KC_BTN4,
  _______, _______, _______, _______, KC_CUT,  _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R,
  _______, _______, _______, _______, KC_CPY,  _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|ColmDH|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |KC_AST|Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  RESET,   DEBUG,   _______, _______, _______, _______, _______, TERM_ON, TERM_OFF, _______, _______, KC_DEL,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  COLEMDH, _______,
  KC_ASTG, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, RGB_SAI,  RGB_SAD, RGB_VAI, RGB_VAD,
  BL_TOGG, BL_STEP, _______, _______, _______, _______, _______, _______, RGB_TOG,  RGB_MOD, RGB_HUI, RGB_HUD
),

};

// Runs boot tasks for keyboard
void matrix_init_user(void) {
        rgblight_enable();
        rgblight_sethsv(150, 255, 255); // Spring Green
        rgblight_mode(13); // Swirling rainbow
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string.\n");
        set_single_persistent_default_layer(_QWERTY);
        SEND_STRING("\nLayout changed to QWERTY.\n");
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        SEND_STRING("\nLayout changed to COLEMAK.\n");
      }
      return false;
      break;
    case COLEMDH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMDH);
        SEND_STRING("\nLayout changed to COLEMAK MOD DH.\n");
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
        SEND_STRING("\nLayout changed to DVORAK.\n");
      }
      return false;
      break;
  }
  return true;
}
