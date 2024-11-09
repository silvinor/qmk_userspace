// Copyright 2018-2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
// Source: https://github.com/tzarc/qmk_userspace/blob/main/users/tzarc/tzarc_common.c

#include <quantum.h>
#include <report.h>
#include "konami.h"

static void konami_code_handler(void) {
    wait_ms(50);
    reset_keyboard();
}

bool process_record_konami_code(uint16_t keycode, keyrecord_t *record) {
    static uint8_t        konami_index          = 0;
    static const uint16_t konami_code[] PROGMEM = {KC_UP, KC_UP, KC_DOWN, KC_DOWN, KC_LEFT, KC_RIGHT, KC_LEFT, KC_RIGHT, KC_B, KC_A /*, KC_ENTER */ };

    if (!record->event.pressed) {
        switch (keycode) {
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                // Messing with layers, ignore but don't reset the counter.
                break;
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                return process_record_konami_code(QK_MOD_TAP_GET_TAP_KEYCODE(keycode), record);
                break;
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                return process_record_konami_code(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode), record);
                break;
            case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
                return process_record_konami_code(QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode), record);
                break;
            // case KC_KP_ENTER:
            // case KC_RETURN:
            // case QK_SPACE_CADET_RIGHT_SHIFT_ENTER:
            //     return process_record_konami_code(KC_ENTER, record);
            //     break;
            case KC_UP:
            case KC_DOWN:
            case KC_LEFT:
            case KC_RIGHT:
            case KC_B:
            case KC_A:
            // case KC_ENTER:
                if (keycode == pgm_read_word(&konami_code[konami_index])) {
                    // next key in sequence
                    konami_index++;
                    if (konami_index == ARRAY_SIZE(konami_code)) {
                        // at end
                        konami_index = 0;
                        konami_code_handler();
                    }
                } else {
                    konami_index = 0;  // reset
                }
                break;
            default:
                konami_index = 0;  // reset
                break;
        }
    }
    return true;
}
