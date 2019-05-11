#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

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

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#define KEYLOG_LEN (int)(32 / OLED_FONT_WIDTH)
char keylog_str[KEYLOG_LEN] = {};
uint8_t keylogs_str_idx = 0;
uint16_t log_timer = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {  add_keylog(keycode); }
    return true;
}

void render_status(void) {

    oled_write_P(PSTR("Layer"), false);
    switch (biton32(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _MODDH:
            oled_write_P(PSTR("MODDH"), false);
            break;
    }

    uint8_t modifiers = get_mods();
    uint8_t one_shot = get_oneshot_mods();

    oled_write_P(PSTR("Mods:"), false);
    oled_write_P( (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? PSTR(" SFT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL ) ? PSTR(" CTL ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT  ) ? PSTR(" ALT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI  ) ? PSTR(" GUI ") : PSTR("     "), false);


    oled_write_P(PSTR("BTMGK"), false);

    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(PSTR(" Mac "), false);
    } else {
        oled_write_P(PSTR(" Win "), false);
    }

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);

    oled_write(keylog_str, false);
}


void oled_task_user(void) {
    if (is_master) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
        oled_scroll_left();  // Turns on scrolling
    }
}

void matrix_scan_keymap(void) { update_log(); }
#endif
