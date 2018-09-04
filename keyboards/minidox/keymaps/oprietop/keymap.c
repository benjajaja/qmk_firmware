#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _MODDH 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _MOVE 4
#define _VIMOVE 5
#define _ADJUST 16

enum custom_keycodes {
  MODDH = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  MOVE,
  VIMOVE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

// Movement layer when held, Space when tapped
#define KC_MOSP LT(_MOVE, KC_SPC)

// Cut/Paste shortcuts
#define KC_CPY LCTL(KC_INS)
#define KC_CUT LSFT(KC_DEL)
#define KC_PST RSFT(KC_INS)


#define ALTENT ALT_T(KC_ENT)
#define LOWTAB LT(_LOWER, KC_TAB)
#define MOVTAB LT(_MOVE, KC_TAB)
#define CTLSPC CTL_T(KC_SPC)
#define SFTBSPC SFT_T(KC_BSPC)
#define RAIDEL LT(_RAISE, KC_DEL)

#define MOVE MO(_MOVE)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
// OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak Mod-DH
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |           |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| SpcMo|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_MODDH] = LAYOUT( \
  KC_Q,    KC_W,    KC_F,   KC_P,   KC_B,         KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, \
  KC_A,    KC_R,    KC_S,   KC_T,   KC_G,         KC_M,    KC_N,   KC_E,    KC_I,    KC_O,    \
  KC_Z,    KC_X,    KC_C,   KC_D,   KC_V,         KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, \
                 KC_LCTL, LOWTAB, KC_MOSP,        SFTBSPC, RAIDEL, KC_LGUI                    \
),

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| SpcMo|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,         KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,         KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,         KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, \
                 KC_LCTL, LOWTAB, KC_MOSP,        KC_BSPC, RAIDEL, OSM(MOD_LSFT) \
),


/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |      |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Ctrl | Shift| GUI  | Alt  |  Del |           |      |      |   `  |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |ADJUST|      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     \
  KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,  \
  KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_DEL,       _______, _______, KC_GRV,  KC_BSLS,  KC_QUOT, \
                    _______, ADJUST,  _______,      _______, _______,  _______                    \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc | PLAY | PREV | NEXT | STOP |           |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps| MUTE | VOL- | VOL+ | MEDIA|           |      |      |   ~  |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |ADJUST|      |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_ESC,  KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  KC_CAPS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MSEL,      _______, _______, KC_TILD, KC_PIPE,  KC_DQT, \
                    _______, _______, _______,      KC_ENT,  ADJUST,  _______                    \
),

/* Movement
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  Esc | COPY | WH_U | Cut  | Paste|           |  M_1 |  M_U |  M_2 |  M_3 | PGUP |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | WH_L | WH_D | WH_R |  Ins |           |  M_L |  M_D |  M_R |  UP  | PGDN |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Ctrl | Shift| GUI  | Alt  |  Del |           | HOME |  END | LEFT | DOWN | RGTH |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |VIMOVE|      |    |      |      |      |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_MOVE] = LAYOUT( \
  KC_ESC,  KC_COPY, KC_WH_U, KC_CUT,  KC_PST,       KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_PGUP, \
  KC_TAB,  KC_WH_L, KC_WH_D, KC_WH_R, KC_INS,       KC_MS_L, KC_MS_D, KC_MS_R, KC_UP,   KC_PGDN, \
  KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_DEL,       KC_HOME, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, \
                    _______, _______, _______,      KC_ENT,  _______, _______                    \
),

/* VIM Movement (Testing)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  Esc |  CUT | COPY | PASTE|      |           |      | M_L  |  M_D |  M_U | M_L  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |  M_1 |  M_3 | M_2  | Ins  |           |      | LEFT | DOWN |  UP  | LEFT |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Ctrl | Shift| GUI  | Alt  | Del  |           |      | HOME | PGDN | PGUP | END  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_VIMOVE] = LAYOUT( \
  KC_ESC,  KC_CUT,  KC_CPY,  KC_PST,  _______,      _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
  KC_TAB,  KC_BTN1, KC_BTN3, KC_BTN2, KC_INS,       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_DEL,       _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  \
                    _______, _______, _______,      _______, _______, _______                    \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |RGBHUI|RGBSAI|RGBVAI|           |M_ACL0|M_ACL1|M_ACL2|Taskmg|caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |RGBTOG|RGBMOD|RGBHUD|RGBSAD|RGBVAD|           |      |      |      |MODDH |QWERTY|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |RESET |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
  KC_F11,  KC_F12,  RGB_HUI, RGB_SAI, RGB_VAI,      KC_ACL0, KC_ACL1, KC_ACL2, TSKMGR,  CALTDEL, \
  RGB_TOG, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,      _______, _______, _______, MODDH,   QWERTY,  \
                    RESET,   _______, _______,      _______, _______, _______                    \
)
};

void matrix_init_user(void) { // Runs boot tasks for keyboard
    rgblight_enable();
    rgblight_sethsv(340, 255, 255); // Red Magenta
    rgblight_mode(3);
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MODDH:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_MODDH);
        SEND_STRING("\nLayout changed to COLEMAK MOD-DH.\n");
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
        SEND_STRING("\nLayout changed to QWERTY.\n");
      }
      return false;
      break;
  }
  return true;
};
