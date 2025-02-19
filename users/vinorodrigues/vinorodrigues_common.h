// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <action.h>

#ifdef RGB_MATRIX_ENABLE
rgb_t adjust_to_brightness(uint8_t r, uint8_t g, uint8_t b, uint8_t min, uint8_t max);
#endif // RGB_MATRIX_ENABLE

bool kc_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2);
bool kc_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3);

uint8_t get_random_number(uint8_t min, uint8_t max);

// uint16_t find_key_index(uint16_t target_keycode);
