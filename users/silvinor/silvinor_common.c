// Copyright 2023-2024 Silvino R. (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include <quantum.h>
#include <stdlib.h>
#include <timer.h>
#include <report.h>
#include <action.h>
#ifdef RGB_MATRIX_ENABLE
#    include <color.h>
#endif // RGB_MATRIX_ENABLE
#include "silvinor_common.h"

bool is_randomized = false;

bool kc_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
    } else {
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

bool kc_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
        register_code(data3);
    } else {
        unregister_code(data3);
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

#ifdef RGB_MATRIX_ENABLE

uint8_t __adjust_for_val(uint8_t val, uint8_t twofivefive) {
    int16_t i = (int16_t)(val * (twofivefive / 255.0));
    if (i > 255) { i = 255; }
    if (i < 0) { i = 0; }
    return (uint8_t)i;
}

/*
 * Adjust an RGB color for the current brightness value
 */
rgb_t adjust_to_brightness(uint8_t r, uint8_t g, uint8_t b, uint8_t min, uint8_t max) {
    rgb_t ret = {r: 0, g: 0, b: 0};

    uint8_t brightness = rgblight_get_val();
    if (min > max) {
        uint8_t temp = min;
        min = max;
        max = temp;
    }
    if (brightness > max) brightness = max;
    if (brightness < min) brightness = min;

    ret.r = __adjust_for_val(r, brightness);
    ret.g = __adjust_for_val(g, brightness);
    ret.b = __adjust_for_val(b, brightness);

    return ret;
}

#endif // RGB_MATRIX_ENABLE

/*
 * Generate a random number
 */
uint8_t get_random_number(uint8_t min, uint8_t max) {
    if (!is_randomized) {
        is_randomized = true;
        srand(timer_read());
    }
    if (min > max) {
        uint8_t temp = min;
        min = max;
        max = temp;
    }
    return min + (rand() % (max - min + 1));
}

// uint16_t find_key_index(uint16_t target_keycode) {
//     if (target_keycode == KC_NO) return UINT16_MAX;

//     for (int row = 0; row < MATRIX_ROWS; ++row) {
//         for (int col = 0; col < MATRIX_COLS; ++col) {
//             // TODO: This looks at layer 0 ... what if it's on another layer?
//             uint16_t ret = keymap_key_to_keycode(0, (keypos_t){ .row = row, .col = col });
//             if (ret == target_keycode) {
//                 return ret;
//             }
//         }
//     }
//     // not found
//     return UINT16_MAX;
// }
