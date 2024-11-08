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

// bool is_caffeine_init = false;         // Has rand() been initialised?
bool is_caffeine_on = false;           // No Screen Saver
uint32_t timer_caffeine_buffer = 0; // No Screen Saver timer buffer

#ifdef RGB_MATRIX_ENABLE
uint8_t caffeine_key_index = UINT8_MAX;
RGB caffeine_color;
bool is_blink_rgb_on = false;           // Blink LED timer buffer
uint32_t timer_blink_rgb_buffer = 0; // Blink LED timer buffer
#endif // RGB_MATRIX_ENABLE

#ifdef LED_CAFFIENE_PIN
bool is_blink_led_on = false;
uint32_t timer_blink_led_buffer = 0;
#endif // LED_CAFFIENE_PIN

#ifdef RGB_MATRIX_ENABLE
#    ifndef CAFFEINE_RGB_BLINK_DELAY
#        define CAFFEINE_RGB_BLINK_DELAY 1000
#    endif  // CAFFEINE_RGB_BLINK_DELAY
#endif // RGB_MATRIX_ENABLE
#ifdef LED_CAFFIENE_PIN
#    ifndef CAFFEINE_LED_BLINK_DELAY
#        define CAFFEINE_LED_BLINK_DELAY 500
#    endif  // CAFFEINE_LED_BLINK_DELAY
#endif // LED_CAFFIENE_PIN

#ifndef CAFFEINE_KEY_DELAY
#    define CAFFEINE_KEY_DELAY 59000 // 1 sec shy of 1 minute
#endif // CAFFEINE_KEY_DELAY

#ifndef CAFFEINE_KEY_CODE
#    define CAFFEINE_KEY_CODE KC_RIGHT_CTRL  // Right Control
#endif // CAFFEINE_KEY_CODE

#ifdef LED_CAFFIENE_PIN

static void __caffeine_blink_led(void) {
    if (is_caffeine_on) {
        if (sync_timer_elapsed32(timer_blink_led_buffer) > CAFFEINE_LED_BLINK_DELAY) {  // every second
            timer_blink_led_buffer = sync_timer_read32();  // reset timer
            is_blink_led_on = !is_blink_led_on;
        }

        gpio_write_pin(LED_CAFFIENE_PIN, (is_blink_led_on ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE));
    }
}

#endif // LED_CAFFIENE_PIN

void matrix_scan_caffeine(void) {
    if (is_caffeine_on) {

        /* Keycode and Mouse Jiggle code */

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

        /* LED Blink code */
        #ifdef LED_CAFFIENE_PIN
        __caffeine_blink_led();
        #endif // LED_CAFFIENE_PIN
    }
}

void housekeeping_task_caffeine(void) {
    #ifdef RGB_MATRIX_ENABLE
    // switch off blinking if RGB has been toggled off
    if (is_blink_rgb_on && !rgb_matrix_is_enabled()) {
        is_blink_rgb_on = false;
        if (caffeine_key_index != UINT8_MAX) {
            rgb_matrix_set_color(caffeine_key_index, RGB_OFF);
        }
    }
    #endif // RGB_MATRIX_ENABLE

    #ifdef LED_CAFFIENE_PIN
    if (is_blink_led_on && !is_caffeine_on) {
       is_blink_led_on = false;
       gpio_write_pin(LED_CAFFIENE_PIN, !LED_PIN_ON_STATE);  // switch off LED
    }
    #endif // LED_CAFFIENE_PIN
}

/*
//// shoudn't need this and the declarations set the values
static void __caffeine_init(void) {
    if (!is_caffeine_init) {

        is_caffeine_on = false;
        timer_caffeine_buffer = 0;

        #ifdef RGB_MATRIX_ENABLE
        is_blink_rgb_on = false;
        timer_blink_rgb_buffer = 0;
        #endif // RGB_MATRIX_ENABLE

        #ifdef LED_CAFFIENE_PIN
        blink_led_on = false;
        timer_blink_led_buffer = 0;
        #endif // LED_CAFFIENE_PIN

        is_caffeine_init = true;
    }
}
*/

#ifdef RGB_MATRIX_ENABLE

static void __caffeine_blink_rgb(void) {
    RGB rgb = caffeine_color;

    if (is_caffeine_on && rgb_matrix_is_enabled()) {
        if (sync_timer_elapsed32(timer_blink_rgb_buffer) > CAFFEINE_RGB_BLINK_DELAY) {  // every second
            timer_blink_rgb_buffer = sync_timer_read32();  // reset timer
            is_blink_rgb_on = !is_blink_rgb_on;
            if (is_blink_rgb_on) {
                caffeine_color.r = get_random_number(128, 255);
                caffeine_color.g = get_random_number(128, 255);
                caffeine_color.b = get_random_number(128, 255);
                rgb = adjust_to_brightness(caffeine_color.r, caffeine_color.g, caffeine_color.b, 64, RGB_MATRIX_MAXIMUM_BRIGHTNESS);  // min: 64 is 255 / 4, or 1/4 bright
                caffeine_color = rgb;
            }
        }
    }

    if (/* is_caffeine_init && */ (caffeine_key_index != UINT8_MAX) && is_blink_rgb_on) {
        rgb_matrix_set_color(caffeine_key_index, rgb.r, rgb.g, rgb.b);
    }
}


bool rgb_matrix_indicators_caffeine(void) {
    __caffeine_blink_rgb();
    return true;
}

#endif  // RGB_MATRIX_ENABLE

#ifdef LED_CAFFIENE_PIN

void led_init_ports_caffeine(void) {
    gpio_set_pin_output(LED_CAFFIENE_PIN);
    gpio_write_pin(LED_CAFFIENE_PIN, !LED_PIN_ON_STATE);
}

#endif // LED_CAFFIENE_PIN

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

bool caffeine_process_on_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = true;
        tap_code(CAFFEINE_KEY_CODE);  // dummy tap the default keycode so that the kb registers a key tap
        #ifdef RGB_MATRIX_ENABLE
        caffeine_key_index = g_led_config.matrix_co[record->event.key.row][record->event.key.col];  // bink the key that was pressed
        #endif // RGB_MATRIX_ENABLE
        timer_caffeine_buffer = sync_timer_read32();  // start the timer
    }
    return false;
}

bool caffeine_process_off_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = false;

        #ifdef RGB_MATRIX_ENABLE
        caffeine_key_index = UINT8_MAX;
        is_blink_rgb_on = false;
        #endif  // RGB_MATRIX_ENABLE

        #ifdef LED_CAFFIENE_PIN
        // do nothing, pass to housekeeping task
        #endif // LED_CAFFIENE_PIN
    }
    return false;
}

bool caffeine_process_toggle_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = !is_caffeine_on;
        if (is_caffeine_on) {
            return caffeine_process_on_keycode(record);
        } else {
            return caffeine_process_off_keycode(record);
        }
    }
    return false;
}
