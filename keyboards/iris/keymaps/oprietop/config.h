/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

//#define USE_SERIAL
#define USE_I2C
#define MASTER_LEFT
//#define MASTER_RIGHT
//#define EE_HANDS

//#define BACKLIGHT_BREATHING

#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

// https://github.com/qmk/qmk_firmware/blob/481797f92f2164d06a948eba9bbb91616d378e68/docs/Key-Functions.md
#define PERMISSIVE_HOLD

// https://docs.qmk.fm/#/feature_auto_shif
//#define AUTO_SHIFT_TIMEOUT 175

// https://docs.qmk.fm/#/feature_tap_dance
#define TAPPING_TERM 175

#endif
