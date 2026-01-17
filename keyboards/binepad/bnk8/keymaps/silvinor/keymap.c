// Copyright 2025 Silvinor R. (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

#include "bnk8.h"

#ifdef VIAL_PROTOCOL_VERSION
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
#    include "sr_caffeine.h"
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

// ---------- Optional Add-ons -----------

#if defined(RGB_MATRIX_ENABLE) && defined(COMMUNITY_MODULE_SR_CAFFEINE_ENABLE)

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_indicators_sr_caffeine()) return false;
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_sr_caffeine();
}

// !! : Not needed when used as a module
// void housekeeping_task_user(void) {
//     housekeeping_task_caffeine();
// }

#endif // All the optionals

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
        // !! : no, it's not duplication, this is for VIA keymaps
        case QK_KB_0:
            return process_keycode_sr_caffeine_toggle(record);
            break;
#endif

        case QK_KB_1:
            if (record->event.pressed) {
                uint8_t next_layer = (get_highest_layer(layer_state) + 1) % DYNAMIC_KEYMAP_LAYER_COUNT;
                layer_move(next_layer);
            }
            return false;
            break;

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case QK_KB_9:
            return process_record_sr_version(COMMUNITY_MODULE_SEND_VERSION, record);
            break;
#endif
    }

    return true;
}
