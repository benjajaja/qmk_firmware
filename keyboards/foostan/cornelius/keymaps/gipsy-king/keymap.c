/* Copyright 2021 gipsy-king
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

#define LAYER_BASE 0
#define LAYER_RAISE 1
#define LAYER_XMONAD 2
#define LAYER_FN 3
#define LAYER_SHORTCUTS 4

// Select raise layer, or enter on tap.
#define RAISE LT(LAYER_RAISE, KC_ENT)
// Select xmonad layer with LALT always on, as that is the xmonad modifier key.
#define MOD4 LM(LAYER_XMONAD, MOD_LALT)
// Select fn layer, or mic-mute-tap (F20 is XF86AudioMicMute).
#define FNLAY LT(LAYER_FN, KC_F20)
// Oneshot fn layer.
#define ONESHOT OSL(LAYER_FN)
// Select shortcuts layer with LCTRL always on.
#define CTRL LM(LAYER_SHORTCUTS, MOD_LCTL)

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    EMAIL_W,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty base layer
 * .-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Backsp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   -  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LCtr | LGUI | LAlt | Mod4 | Shift| Space|Ent/Ra| Shift| RALT | RGUI |  FN  |Onesht|
 * '-----------------------------------------------------------------------------------'
 */
[0] = LAYOUT(
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
  KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
  KC_MINS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_EQL,
  CTRL,   KC_LGUI,KC_LGUI,MOD4,   KC_LSFT,KC_SPC, RAISE,  KC_RSFT,KC_RALT,KC_RGUI,FNLAY,  ONESHOT
),
/* Raise layer
 * .-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ~  |   {  | PgUp | PgDn |  End | Home | Left | Down |  Up  | Right|   }  |   |  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   [  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   ]  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * '-----------------------------------------------------------------------------------'
 */
[LAYER_RAISE] = LAYOUT(
  KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,
  KC_TILD,KC_LCBR,KC_PGUP,KC_PGDN,KC_END, KC_HOME,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_RCBR,KC_PIPE,
  KC_LBRC,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_RBRC,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),
/* Xmonad layer (needs Left-Alt)
 * Top row: Quit, Workspaces, Ctrl-P
 * Middle row: Screens, Float, HJKL
 * Bottom row: Shift, Close, Struts
 * Thumbs: Shifts, Space, Enter, Shifts
 * .-----------------------------------------------------------------------------------.
 * |   Q  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   P  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |   W  |   E  |   R  |   T  |   H  |   J  |   K  |   L  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |   C  |      |   B  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Shift| Space| Enter| Shift|      |      |      |      |
 * '-----------------------------------------------------------------------------------'
 */
[LAYER_XMONAD] = LAYOUT(
  KC_Q,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_P,   _______,
  _______,_______,KC_W,   KC_E,   KC_R,   KC_T,   KC_H,   KC_J,   KC_K,   KC_L,   _______,_______,
  KC_LSFT,_______,_______,KC_C,   _______,KC_B,   _______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,KC_LSFT,KC_SPC, KC_ENT, KC_LSFT,_______,_______,_______,_______
),
/* Fn layer
 * FN keys
 * Email Macros, Keyboard Reset, HJKL as Mouse-move-keys
 * Mouse button 1, Mute, Volume, Brightness
 */
[LAYER_FN] = LAYOUT(
  KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
  _______,EMAIL_W,EMAIL,  _______,_______,_______,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,
  RESET,  _______,_______,_______,_______,_______,KC_BTN1,KC_MUTE,KC_VOLD,KC_VOLU,KC_BRID,KC_BRIU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),
/* Shortcuts layer (needs Ctrl)
 * This is crutch layer, because getting ctrl + pgup/down is very awkward, having to use too many
 * fingers.
 * This is an almost standard shortcut to navigate tabs in most apps, like browsers or editors.
 */
[LAYER_SHORTCUTS] = LAYOUT(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_PGUP,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
)
};

/* Simple macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case EMAIL:
                SEND_STRING("ste3ls@gmail.com");
                break;
            case EMAIL_W:
                SEND_STRING("benjamin.grosse@re-cap.com");
                break;
        }
    }
    return true;
};
