// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include <quantum.h>
#include <report.h>
#include "vinorodrigues_common.h"
#include "caffeine.h"

// needed for rand()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #ifdef CONSOLE_ENABLE
// #include "print.h"
// #endif

bool caffeine_init = false;          // Has rand() been initialised?
bool caffeine_on = false;            // No Screen Saver
uint32_t timer_caffeine_buffer = 0;  // No Screen Saver timer buffer
uint8_t caffeine_key_index = UINT8_MAX;

#ifdef RGB_MATRIX_ENABLE

RGB caffeine_color;
bool blink_on = false;            // Blink LED timer buffer
uint32_t timer_blink_buffer = 0;  // Blink LED timer buffer

    #ifndef CAFFEINE_BLINK_DELAY
        #define CAFFEINE_BLINK_DELAY 1000
    #endif  // CAFFEINE_BLINK_DELAY

#endif  // RGB_MATRIX_ENABLE

#ifndef CAFFEINE_KEY_DELAY
    #define CAFFEINE_KEY_DELAY 59000 // 1ms shy of 1 minute
#endif  // CAFFEINE_KEY_DELAY

#ifndef CAFFEINE_KEY_CODE
    #define CAFFEINE_KEY_CODE KC_RIGHT_CTRL  // Right Control
#endif  // CAFFEINE_KEY_CODE

void matrix_scan_caffeine(void) {
    if (caffeine_on) {
        if (sync_timer_elapsed32(timer_caffeine_buffer) > CAFFEINE_KEY_DELAY) { // default = 59 sec
            timer_caffeine_buffer = sync_timer_read32(); // reset timer
            // --- tap a key ---
            tap_code(CAFFEINE_KEY_CODE);
            #ifdef MOUSEKEY_ENABLE
            // --- jiggle the mouse ---
            uint8_t r = rand() % 4;  // randomize mouse moves
            switch (r) {
                case 0:
                    tap_code(KC_MS_UP);
                    tap_code(KC_MS_DOWN);
                    break;
                case 1:
                    tap_code(KC_MS_LEFT);
                    tap_code(KC_MS_RIGHT);
                    break;
                case 2:
                    tap_code(KC_MS_DOWN);
                    tap_code(KC_MS_UP);
                    break;
                case 3:
                    tap_code(KC_MS_RIGHT);
                    tap_code(KC_MS_LEFT);
                    break;
            }
            #endif // MOUSEKEY_ENABLE
        }
    }
}

void housekeeping_task_caffeine(void) {
    // switch off blinking if RGB has been toggled off
    if (blink_on && !rgb_matrix_is_enabled()) {
        blink_on = false;
        if (caffeine_key_index != UINT8_MAX)
            rgb_matrix_set_color(caffeine_key_index, RGB_OFF);
    }
}

#ifdef RGB_MATRIX_ENABLE

static void __caffeine_init(void) {
    if (!caffeine_init) {
        caffeine_on = false;
        timer_caffeine_buffer = 0;
        #ifdef RGB_MATRIX_ENABLE
        blink_on = false;
        timer_blink_buffer = 0;
        #endif  // RGB_MATRIX_ENABLE

        caffeine_init = true;
    }
}

static void __caffeine_blink(void) {
    RGB rgb = caffeine_color;

    if (caffeine_on && rgb_matrix_is_enabled()) {
        if (sync_timer_elapsed32(timer_blink_buffer) > CAFFEINE_BLINK_DELAY) {  // every second
            timer_blink_buffer = sync_timer_read32();  // reset timer
            blink_on = !blink_on;
            if (blink_on) {
                caffeine_color.r = get_random_number(128, 255);
                caffeine_color.g = get_random_number(128, 255);
                caffeine_color.b = get_random_number(128, 255);
                rgb = adjust_to_brightness(caffeine_color.r, caffeine_color.g, caffeine_color.b, 64, 255);  // min: 64 is 255 / 4, or 1/4 bright
                caffeine_color = rgb;
            }
        }
    }

    if (caffeine_init && (caffeine_key_index != UINT8_MAX) && blink_on) {
        rgb_matrix_set_color(caffeine_key_index, rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_caffeine(void) {
    __caffeine_blink();
    return true;
}

bool led_update_caffeine(led_t led_state) {
    __caffeine_blink();
    return true;
}

#endif  // RGB_MATRIX_ENABLE

// void keyboard_post_init_caffeine(void) {
//     // #ifdef CONSOLE_ENABLE
//     // dprint("f: keyboard_post_init_caffeine");
//     // #endif
// }

// void eeconfig_init_caffeine(void) {
//     // #ifdef CONSOLE_ENABLE
//     // dprint("f: eeconfig_init_caffeine");
//     // #endif
// }

bool caffeine_process_toggle_keycode(keyrecord_t *record) {
    if (!caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        caffeine_on = !caffeine_on;
        if (caffeine_on) {
            tap_code(CAFFEINE_KEY_CODE);  // dummy tap the default keycode so that the kb registers a key tap
            caffeine_key_index = g_led_config.matrix_co[record->event.key.row][record->event.key.col];  // bink the key that was pressed
            timer_caffeine_buffer = sync_timer_read32();  // start the timer
        } else {
            #ifdef RGB_MATRIX_ENABLE
            blink_on = false;
            #endif  // RGB_MATRIX_ENABLE
            caffeine_key_index = UINT8_MAX;
        }
    }

    // #ifdef CONSOLE_ENABLE
    // dprintf("function: __set_led_index, index: %u, value: %u \n", index, caffeine_key_index);
    // #endif

    return false;
}
