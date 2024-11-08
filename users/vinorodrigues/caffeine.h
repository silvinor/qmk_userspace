// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

void matrix_scan_caffeine(void);
void housekeeping_task_caffeine(void);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_caffeine(void);
#endif  // RGB_MATRIX_ENABLE

#ifdef LED_CAFFIENE_PIN
void led_init_ports_caffeine(void);
#endif // LED_CAFFIENE_PIN

// void keyboard_post_init_caffeine(void);
// void eeconfig_init_caffeine(void);

bool caffeine_process_on_keycode(keyrecord_t *record);
bool caffeine_process_off_keycode(keyrecord_t *record);
bool caffeine_process_toggle_keycode(keyrecord_t *record);
