#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Mouse Settings */
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

// https://docs.qmk.fm/#/feature_auto_shif
//define AUTO_SHIFT_TIMEOUT 175

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
#define PERMISSIVE_HOLD
#define PREVENT_STUCK_MODIFIERS
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif // TAPPING_TERM
#define TAPPING_TERM 100

#endif
