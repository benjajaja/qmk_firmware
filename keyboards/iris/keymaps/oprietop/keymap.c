#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMDH 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMDH,
  LOWER,
  RAISE,
  LODE,
  RABS,
};

#define KC_     KC_TRNS
#define KC_QWER QWERTY
#define KC_COLH COLEMDH
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_BL_S BL_STEP
#define KC_BL_B BL_BRTG
#define KC_DBUG DEBUG

// MOmentary layer switch
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Shift when held, Enter when tapped
#define KC_LSEN LSFT_T(KC_ENT)
#define KC_RSEN RSFT_T(KC_ENT)

// Shift when held, Space when tapped
#define KC_LSSP LSFT_T(KC_SPC)
// Lower when held, Delete when tapped
#define KC_LODE LT(_LOWER, KC_DEL)

// Raise when held, Backspace when tapped
#define KC_RABS LT(_RAISE, KC_BSPC)

// Cut/Paste shortcuts
#define KC_CPY LCTL(KC_INS)
#define KC_PST RSFT(KC_INS)
#define KC_CUT LSFT(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSEN, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,RSEN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,HOME,     END , N  , M  ,COMM,DOT ,SLSH,RALT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LODE,LSSP,         RSEN,RABS,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_COLEMDH] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , B  ,                J  , L  , U  , Y  ,SCLN,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSEN, A  , R  , S  , T  , G  ,                M  , N  , E  , I  , O  ,RSEN,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , D  , V  ,HOME,     END , K  , H  ,COMM,DOT ,SLSH,RALT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LODE,LSSP,         RSEN,RABS,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,PGUP,BTN1,BTN3,BTN2,LPRN,               RPRN,BTN1,MS_U,BTN2,BTN3,PIPE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,PGDN,LEFT,RGHT, UP ,LBRC,               RBRC,MS_L,MS_D,MS_R, UP ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,INS ,HOME,END ,DOWN,LCBR, CPY,     PST ,RCBR,PLUS,MINS,LEFT,DOWN,RGHT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MPRV,MNXT,VOLU,PGUP,UNDS,               EQL ,HOME,INS ,ESC ,PGUP,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS, CPY,     PST ,PLUS,END ,DEL ,HOME,PGDN,END ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     RST ,QWER,COLH,    ,    ,    ,               DBUG,    ,    ,    ,    ,PSCR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     DBUG,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CAPS,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,CAPS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,BL_B,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )

};

// Handle Tri layer (Lower + Raise) with LT support
// https://github.com/msandiford/qmk_firmware/commit/de5b55a6c5e14bf54d77db6ac5a7d8c5cb2c9d7c
#define LOWER_AND_RAISE ((1UL << _LOWER) | (1UL << _RAISE))

uint32_t layer_state_set_kb(uint32_t state) {
  if ((state & LOWER_AND_RAISE) == LOWER_AND_RAISE) {
    state |= 1UL << _ADJUST;
  } else {
    state &= ~(1UL << _ADJUST);
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        SEND_STRING(" Layout changed to QWERTY ");
      }
      return false;
      break;
    case COLEMDH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMDH);
        SEND_STRING(" Layout changed to COLEMAK MOD DH ");
      }
      return false;
      break;
  }
  return true;
}

