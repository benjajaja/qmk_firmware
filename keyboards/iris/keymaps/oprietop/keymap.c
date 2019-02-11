#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Macros
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMDH,
};

// Layers
#define _QWERTY 0
#define _COLEMDH 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

// Aliases
#define KC_     KC_TRNS
#define KC_QWER QWERTY
#define KC_COLH COLEMDH
#define KC_ADJU MO(_ADJUST)
#define KC_RST  RESET
#define KC_BL_S BL_STEP
#define KC_BL_B BL_BRTG
#define KC_DBUG DEBUG
// Shift when held, Backspace when tapped
#define KC_LSBS LSFT_T(KC_BSPC)
#define KC_RSBS RSFT_T(KC_BSPC)
// Shift when held, Enter when tapped
#define KC_LSEN LSFT_T(KC_ENT)
#define KC_RSEN RSFT_T(KC_ENT)
// Shift when held, Quote when tapped
#define KC_RSQU RSFT_T(KC_QUOTE)
// Lower when held, Space when tapped
#define KC_LOSP LT(_LOWER, KC_SPC)
// Alt when held, Tab when tapped
#define KC_ALTA LALT_T(KC_TAB)
// RAlt when held, Tab when tapped
#define KC_RATA RALT_T(KC_TAB)
// Raise when held, Delete when tapped
#define KC_RADE LT(_RAISE, KC_DEL)
// Cut/Paste shortcuts
#define KC_CPY LCTL(KC_INS)
#define KC_PST RSFT(KC_INS)
#define KC_CUT LSFT(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LSBS, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,RSQU,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,HOME,     END , N  , M  ,COMM,DOT ,SLSH,RCTL,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,RATA,LOSP,         RSBS,RADE,LALT
  //                  `----+----+----'        `----+----+----'
  ),

  [_COLEMDH] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    , F  , P  , B  ,                J  , L  , U  , Y  ,SCLN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         , A  , R  , S  , T  ,    ,                M  , N  , E  , I  , O  ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    , D  , V  ,    ,         , K  , H  ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,F11 ,F12 ,WH_U,CUT ,PST ,               BTN1,MS_U,BTN2,BTN3,PGUP,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,HOME,WH_L,WH_D,WH_R,INS ,               MS_L,MS_D,MS_R, UP ,PGDN,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,END ,ACL0,ACL1,ACL2,DEL ,CPY ,     BSPC,HOME,END ,LEFT,DOWN,RGHT,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,         ENT ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,F11 ,F12 ,MPRV,MNXT,VOLU,               TILD,UNDS,PLUS,LCBR,RCBR,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MPRV,MNXT,MSTP,MPLY,VOLD,               GRV ,MINS,EQL ,LBRC,RBRC,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MUTE,    ,    ,    ,    ,CPY ,     PST ,BSLS,PIPE,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,ADJU,    ,             ,    ,
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

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

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
