// Copyright 2023 Silvino R. (@silvinor)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef COMMUNITY_MODULE_SR_COMMON_ENABLE
#    include "sr_common.h"
#endif

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
#    include "sr_caffeine.h"
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

#ifdef COMMUNITY_MODULE_GLOBE_KEY_ENABLE
// forward prototype because there is no `globe_key.h`
bool process_record_globe_key(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef COMMUNITY_MODULE_SOCD_CLEANER_ENABLE
// clang-format off
socd_cleaner_t socd_opposing_pairs[] = {
    {{KC_W, KC_S}, SOCD_CLEANER_LAST},
    {{KC_A, KC_D}, SOCD_CLEANER_LAST},
    {{KC_UP, KC_DOWN}, SOCD_CLEANER_LAST},
    {{KC_LEFT, KC_RGHT}, SOCD_CLEANER_LAST}
};
// clang-format on
#endif

// clang-format off
enum {
    CK_MISSION_CONTROL = QK_KB_0,
    CK_LAUNCHPAD,     // QK_KB_1
    CK_SIRI,          // QK_KB_2
    CK_GLOBE_KEY,     // QK_KB_3
    CK_SCREEN_SHOT,   // QK_KB_4
    CK_TASK_VIEW,     // QK_KB_5
    CK_FILE_EXPLORER, // QK_KB_6
    CK_CORTANA,       // QK_KB_7
    CK_CAFFEINE,      // QK_KB_8
    CK_VERSION        // QK_KB_9
} custom_keycodes_t;
// clang-format on

// 7-char variants for manual keymap
#define CK_MCTL CK_MISSION_CONTROL
#define CK_LPAD CK_LAUNCHPAD
#define CK_GLOB CK_GLOBE_KEY
#define CK_SNAP CK_SCREEN_SHOT
#define CK_TASK CK_TASK_VIEW
#define CK_FLXP CK_FILE_EXPLORER
#define CK_CRTA CK_CORTANA
#define CK_COFY CK_CAFFEINE
#define CK_VRSN CK_VERSION

#ifdef MATRIX_MASKED // Lockout any unuse keys, because "why not".
// clang-format off
const matrix_row_t matrix_mask[] = {
    0b111111111111111111,
    0b111111111111111111,
    0b111111111111111111,
    0b011110111111111111,
    0b111111111111111101,
    0b011111110001000111
};
// clang-format on
#endif

// ---------------------------------------------------------------------------
void led_init_ports(void) {
    // TODO : Have not figured out the PWM functions yet, not all RP API is ported to QMK

#ifndef OPENDRAIN_INDICATORS
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_PUSHPULL
#else
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_OPENDRAIN
#endif

    const uint8_t led_pins[] = {
#ifdef PWM_CAPS_LOCK_PIN
        PWM_CAPS_LOCK_PIN,
#endif
#ifdef PWM_NUM_LOCK_PIN
        PWM_NUM_LOCK_PIN,
#endif
    };
    for (uint8_t i = 0; i < sizeof(led_pins); i++) {
        uint8_t pin = led_pins[i];

        palSetLineMode(pin, INDICATOR_PIN_MODE);
        gpio_write_pin(pin, !LED_PIN_ON_STATE);
    }
}

// ---------------------------------------------------------------------------
//// void led_update_ports(led_t led_state) {
bool led_update_user(led_t led_state) {
#ifdef PWM_CAPS_LOCK_PIN
    gpio_write_pin(PWM_CAPS_LOCK_PIN, led_state.caps_lock ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE);
#endif

#ifdef PWM_NUM_LOCK_PIN
    uint8_t layer       = get_highest_layer(layer_state | default_layer_state);
    bool    is_num_lock = led_state.num_lock || (layer == 1);
    gpio_write_pin(PWM_NUM_LOCK_PIN, is_num_lock ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE);
#endif

    led_update_caffeine(led_state);

    return false; // false = override the keyboard level code
}

//// ---------------------------------------------------------------------------
// #ifdef FAKE_VIA_PROTOCOL_VERSION
// bool via_command_kb(uint8_t *data, uint8_t length) {
//     uint8_t *command_id   = &(data[0]);
//     uint8_t *command_data = &(data[1]);
//     switch (*command_id) {
//         // override default get version
//         case id_get_protocol_version:
//             command_data[0] = FAKE_VIA_PROTOCOL_VERSION >> 8;
//             command_data[1] = FAKE_VIA_PROTOCOL_VERSION & 0xFF;
//             return true; // override default handler
//             break;
//     }
//     return false;
// }
// #endif

// ---------------------------------------------------------------------------
#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
void matrix_scan_user(void) {
    matrix_scan_caffeine();
}
#endif

// ---------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            // ----- macOS -----

        case CK_MISSION_CONTROL: // legacy, for Vial builds
            // if (record->event.pressed) {
            //     register_code(KC_MISSION_CONTROL);
            // } else {
            //     unregister_code(KC_MISSION_CONTROL);
            // }
            if (record->event.pressed) {
                host_consumer_send(AC_DESKTOP_SHOW_ALL_WINDOWS);
            } else {
                host_consumer_send(0);
            }
            return false;
            break;

        case CK_LAUNCHPAD: // legacy, for Vial builds
            // if (record->event.pressed) {
            //     register_code(KC_LAUNCHPAD);
            // } else {
            //     unregister_code(KC_LAUNCHPAD);
            // }
            if (record->event.pressed) {
                host_consumer_send(AC_SOFT_KEY_LEFT);
            } else {
                host_consumer_send(0);
            }
            return false;
            break;

#ifdef COMMUNITY_MODULE_SR_COMMON_ENABLE
        case CK_SIRI:
            return kc_register_code_2(record, KC_LOPT, KC_SPACE);
            break;
#endif

#ifdef COMMUNITY_MODULE_GLOBE_KEY_ENABLE
        case CK_GLOBE_KEY:
            // return process_record_globe_key(KC_GLOBE, record);
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
            } else {
                host_consumer_send(0);
            }
            return false;

            break;
#endif

#ifdef COMMUNITY_MODULE_SR_COMMON_ENABLE
        case CK_SCREEN_SHOT:
            return kc_register_code_3(record, KC_LSFT, KC_LCMD, KC_4);
            break;
#endif

            // ----- Windows ------

#ifdef COMMUNITY_MODULE_SR_COMMON_ENABLE

        case CK_TASK_VIEW:
            return kc_register_code_2(record, KC_LWIN, KC_TAB);
            break;

        case CK_FILE_EXPLORER:
            return kc_register_code_2(record, KC_LWIN, KC_E);
            break;

        case CK_CORTANA:
            return kc_register_code_2(record, KC_LWIN, KC_C);
            break;

#endif // COMMUNITY_MODULE_SR_COMMON_ENABLE

            // ------ Other ------

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
        case CK_CAFFEINE:
            return process_keycode_caffeine_toggle(record);
            break;
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case CK_VERSION:
            return process_record_version(COMMUNITY_MODULE_SEND_VERSION, record);
            break;
#endif

        default:
            break;
    }
    return true;
}
