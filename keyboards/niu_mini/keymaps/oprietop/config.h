#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

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
#define TAPPING_TERM 200

#endif
