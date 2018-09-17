#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Mouse Settings */
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

// https://github.com/qmk/qmk_firmware/blob/481797f92f2164d06a948eba9bbb91616d378e68/docs/Key-Functions.md
#define PERMISSIVE_HOLD

// https://docs.qmk.fm/#/feature_auto_shif
#define AUTO_SHIFT_TIMEOUT 175

// https://docs.qmk.fm/#/feature_tap_dance
#define TAPPING_TERM 175

#endif
