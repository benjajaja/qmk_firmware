/* Copyright 2019 Takuya Urakawa (dm9records.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef OLED_DRIVER_ENABLE
#define OLED_DISPLAY_CUSTOM
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 32
#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)  // 1024 (compile time mathed)
#define OLED_BLOCK_TYPE uint16_t
#define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)  // 32 (compile time mathed)
#define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)  // 32 (compile time mathed)
#define OLED_COM_PINS COM_PINS_ALT
#define OLED_SOURCE_MAP { 0, 8, 16, 24}
#define OLED_TARGET_MAP { 24, 16, 8, 0 }
// #define OLED_TIMEOUT 60000
#endif
