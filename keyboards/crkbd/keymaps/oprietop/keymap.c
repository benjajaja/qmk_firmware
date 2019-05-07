#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#include "ssd1306.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Layers
#define _MODDH 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// Shortcuts
#define KC_COPY LCTL(KC_INS)
#define KC_CUT LSFT(KC_DEL)
#define KC_PST RSFT(KC_INS)
#define KC_      KC_TRNS
#define KC_XXXXX KC_NO
#define KC_ADJUS TT(_ADJUST)
#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD

// Left
#define KC_GRV_S LSFT_T(KC_GRV)
#define KC_MIN_C LCTL_T(KC_MINS)
#define KC_Z_GUI LGUI_T(KC_Z)
#define KC_X_ALT LALT_T(KC_X)
#define KC_B_AGR RALT_T(KC_B)
#define KC_LTESC LT(_LOWER, KC_ESC)
#define KC_TAB_S LSFT_T(KC_TAB)
#define KC_LTSPC LT(_LOWER, KC_SPC)
// Right
#define KC_QUO_S RSFT_T(KC_QUOT)
#define KC_EQL_C RCTL_T(KC_EQL)
#define KC_SLS_G RGUI_T(KC_SLSH)
#define KC_DOT_A LALT_T(KC_DOT)
#define KC_J_AGR RALT_T(KC_J)
#define KC_LTBSP LT(_RAISE, KC_BSPC)
#define KC_DEL_S RSFT_T(KC_DEL)
#define KC_LTGUI LT(_RAISE, KC_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MODDH] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       LBRC,     Q,     W,     F,     P, B_AGR,                  J_AGR,     L,     U,     Y,  SCLN,  RBRC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GRV_S,     A,     R,     S,     T,     G,                      M,     N,     E,     I,     O, QUO_S,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      MIN_C, Z_GUI, X_ALT,     C,     D,     V,                      K,     H,  COMM, DOT_A, SLS_G, EQL_C,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LTESC, TAB_S, LTSPC,    LTBSP, DEL_S, LTGUI \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
           ,   ESC,  COPY,  WH_U,   CUT,   PST,                   PGUP,  BTN1,  MS_U,  BTN2,  BTN3,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,   TAB,  WH_L,  WH_D,  WH_R,   INS,                   HOME,  MS_L,  MS_D,  MS_R,   END,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,  LCTL,  LSFT,  LGUI,  BTN1,   DEL,                   PGDN,  LEFT,  DOWN,    UP,  RGHT,      ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,      ENT, ADJUS,       \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       PIPE,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        DOT,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  COMM,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        F11,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,   F12,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       , ADJUS,   ENT,         ,      ,       \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,         ,      ,       \
                              //`--------------------'  `--------------------'
  )
};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  iota_gfx_init(!has_usb());   // turns on the display
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
