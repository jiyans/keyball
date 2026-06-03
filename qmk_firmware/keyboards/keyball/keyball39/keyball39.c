/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "lib/keyball/keyball.h"

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
};
// clang-format on

#ifdef RGB_MATRIX_ENABLE
// Keyball39 uses per-key LEDs, but the two halves are asymmetric: the left
// half has 24 LEDs and the right half has 22. Map matrix positions to the
// actual PCB LED indices so reactive RGB Matrix effects originate from the
// pressed key instead of a rough virtual grid.
led_config_t g_led_config = {{
    {0, 3, 6, 10, 14, NO_LED},
    {1, 4, 7, 11, 15, NO_LED},
    {2, 5, 8, 12, 16, NO_LED},
    {23, 22, 22, 9, 13, 17},
    {30, 34, 37, 40, 43, NO_LED},
    {31, 35, 38, 41, 44, NO_LED},
    {32, 36, 39, 42, 45, NO_LED},
    {33, NO_LED, NO_LED, NO_LED, 24, 24},
}, {
    {22, 9},   {22, 25}, {22, 42}, {42, 6},   {42, 23}, {42, 39},
    {63, 4},   {63, 21}, {63, 37}, {63, 54},  {83, 8},  {83, 25},
    {83, 41},  {83, 58}, {104, 14}, {104, 31}, {104, 47}, {104, 64},
    {42, 10},  {104, 18}, {104, 51}, {63, 41}, {25, 51}, {0, 55},
    {120, 50}, {138, 42}, {173, 36}, {224, 47}, {224, 14}, {163, 6},
    {224, 10}, {224, 27}, {224, 43}, {224, 60}, {204, 4}, {204, 21},
    {204, 37}, {183, 0}, {183, 17}, {183, 33}, {163, 2}, {163, 19},
    {163, 35}, {142, 4}, {142, 21}, {142, 37},
}, {
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
}};
#endif

void keyball_on_adjust_layout(keyball_adjust_t v) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = keyball.this_have_ball ? 22 : 24;
    uint8_t lednum_that = !keyball.that_enable ? 0 : keyball.that_have_ball ? 22 : 24;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}
