#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(ZELDA_PUZZLE)
    // #define STARTUP_SONG SONG(NO_SOUND)
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

/* Mouse Settings */
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
//#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
//#define TAPPING_FORCE_HOLD
//#define TAPPING_TERM 175
