/* (c) 2024 Vino Rodrigues */
/* SPDX-License-Identifier: GPL-3.0-or-later */

#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE
#include <version.h>
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif // RGB_MATRIX_ENABLE
#include "vinorodrigues_common.h"
#ifdef CAFFEINE_ENABLE
#    include "caffeine.h"
#endif // CAFFEINE_ENABLE
#ifdef KONAMI_ENABLE
#    include "konami.h"
#endif // KONAMI_ENABLE
#ifdef SOCD_CLEANER_ENABLE
#    include "socd_cleaner.h"
#endif

enum {
    KC_SIRI = QK_KB_2,
    KC_SCREEN_SHOT,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_CORTANA,
    #ifdef CAFFEINE_ENABLE
    KC_CAFFEINE_ON,
    KC_CAFFEINE_OFF,
    KC_CAFFEINE_TOGGLE,
    #endif // CAFFEINE_ENABLE
    #ifdef SOCD_CLEANER_ENABLE
    KC_SOCD_ON,
    KC_SOCD_OFF,
    KC_SOCD_TOGGLE,
    #endif // SOCD_CLEANER_ENABLE
    KC_VERSION = QK_KB_19
};

#define KC_VRSN KC_VERSION
#define KC_SNAP KC_SCREEN_SHOT
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_CRTA KC_CORTANA
#define RGB_RMD RGB_RMOD
#define KC_RET  KC_RETURN
#ifdef CAFFEINE_ENABLE
#    define KC_CAFF KC_CAFFEINE_TOGGLE
#else
#    define KC_CAFF _______
#endif // CAFFEINE_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define XX NO_LED
// clang-format off
led_config_t g_led_config = {
  {
    {  0,  1,  2,  3,  4,  5,  6, 7,   8,  9, 10, 11, 12, 13, XX, XX, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, XX, XX, 32, 33, 34, XX },
    { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, XX, XX, 50, 51, 52, 53 },
    { 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, XX, 66, XX, XX, 67, 68, 69, XX },
    { 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, XX, XX, 81, 82, XX, 83, 84, 85, 86 },
    { 87, 88, 89, XX, XX, 90, XX, XX, XX, 91, 92, 93, XX, XX, 94, 95, XX, 96, 97, XX },
  },
  {  // generated from: https://xelus.netlify.app/guides/kle_to_rgb_parser
    {  0,0  }, { 15,0  }, { 27,0  }, { 39,0  }, { 51,0  }, { 67,0  }, { 79,0  }, { 91,0  }, {103,0  }, {118,0  }, {130,0  }, {142,0  }, {154,0  }, {170,0  }, {188,0  }, {200,0  }, {212,0  }, {224,0  },
    {  0,15 }, { 12,15 }, { 24,15 }, { 36,15 }, { 48,15 }, { 61,15 }, { 73,15 }, { 85,15 }, { 97,15 }, {109,15 }, {121,15 }, {133,15 }, {145,15 }, {163,15 }, {188,15 }, {200,15 }, {212,15 }, {224,15 },
    {  3,26 }, { 18,26 }, { 30,26 }, { 42,26 }, { 54,26 }, { 67,26 }, { 79,26 }, { 91,26 }, {103,26 }, {115,26 }, {127,26 }, {139,26 }, {151,26 }, {166,26 }, {188,26 }, {200,26 }, {212,26 }, {224,32 },
    {  5,38 }, { 21,38 }, { 33,38 }, { 45,38 }, { 58,38 }, { 70,38 }, { 82,38 }, { 94,38 }, {106,38 }, {118,38 }, {130,38 }, {142,38 }, {162,38 }, {188,38 }, {200,38 }, {212,38 },
    {  8,49 }, { 27,49 }, { 39,49 }, { 51,49 }, { 64,49 }, { 76,49 }, { 88,49 }, {100,49 }, {112,49 }, {124,49 }, {136,49 }, {153,49 }, {173,52 }, {188,49 }, {200,49 }, {212,49 }, {224,55 },
    {  2,61 }, { 17,61 }, { 32,61 }, { 77,61 }, {124,61 }, {142,61 }, {160,64 }, {173,64 }, {185,64 }, {200,61 }, {212,61 }
  },
  { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x0D, 0x04, 0x04, 0x04,
    0x01, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x09, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x01, 0x04, 0x04, 0x04,
    0x01, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x01, 0x01, 0x04, 0x04, 0x04, 0x01,
    0x01, 0x01, 0x01, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04 },
};
// clang-format on
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(  // Base
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SIRI,          KC_SNAP, KC_VOLD, KC_VOLU,  KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TG(1),   KC_PSLS, KC_PAST,  KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME, KC_UP,   KC_PGUP,  KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_LEFT, KC_NO,   KC_RIGHT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,  KC_DOWN, KC_PGDN,  KC_ENT,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RALT,          MO(2),            KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,   KC_DEL),

    [1] = LAYOUT(  // Mac Numlock
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_P7,   KC_P8,   KC_P9,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_P4,   KC_P5,   KC_P6,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, _______, _______,                   _______,                            _______,          _______,          _______, _______, _______, KC_P0,   KC_PDOT),

    [2] = LAYOUT(  // FN1
        KC_CAFF, KC_BRID, KC_BRIU, QK_KB_0, QK_KB_1, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_F13,           KC_F14,  KC_F15,  KC_F16,  KC_F17,
        DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_NUM,  _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          KC_RET,           _______, _______, _______,
        KC_RSFT, _______, QK_BOOT, EE_CLR,  _______, _______, _______, NK_TOGG, _______, _______, _______,                   KC_LSFT, _______, _______, _______, _______, _______,
        KC_RCTL, KC_RALT, KC_RGUI,                   _______,                            MO(3),            _______,          _______, _______, _______, _______, _______)
};
// clang-format on

#ifdef SOCD_CLEANER_ENABLE
socd_cleaner_t socd_ad = {{KC_A, KC_D}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_ws = {{KC_W, KC_S}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_ud = {{KC_UP, KC_DOWN}, SOCD_CLEANER_LAST};
socd_cleaner_t socd_lr = {{KC_LEFT, KC_RGHT}, SOCD_CLEANER_LAST};
#endif // SOCD_CLEANER_ENABLE

void keyboard_post_init_user(void) {
    #ifdef SOCD_CLEANER_ENABLE
    socd_cleaner_enabled = false;  // TODO: Extract from EEPROM last state
    #endif // SOCD_CLEANER_ENABLE

    #ifdef CONSOLE_ENABLE
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
    #endif // CONSOLE_ENABLE
}

#if defined(RGB_MATRIX_ENABLE) && defined(CAFFEINE_ENABLE)
bool rgb_matrix_indicators_user(void) {
    #ifdef CAFFEINE_ENABLE
    if (!rgb_matrix_indicators_caffeine()) return false;
    #endif // CAFFEINE_ENABLE
    return true;
}
#endif

void led_init_ports(void) {
    #ifdef CONSOLE_ENABLE
    print("led_init_ports()\n");
    #endif // CONSOLE_ENABLE

    #ifdef LED_NUM_LOCK_PIN
    gpio_set_pin_output(LED_NUM_LOCK_PIN);
    gpio_write_pin(LED_NUM_LOCK_PIN, !LED_PIN_ON_STATE);
    #endif

    #ifdef LED_CAPS_LOCK_PIN
    gpio_set_pin_output(LED_CAPS_LOCK_PIN);
    gpio_write_pin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
    #endif

    // #ifdef LED_SCROLL_LOCK_PIN
    // gpio_set_pin_output(LED_SCROLL_LOCK_PIN);
    // gpio_write_pin(LED_SCROLL_LOCK_PIN, !LED_PIN_ON_STATE);
    // #endif

    #if defined(CAFFEINE_ENABLE) && defined(LED_CAFFIENE_PIN)
    led_init_ports_caffeine();
    #endif // CAFFEINE_ENABLE && LED_CAFFIENE_PIN
}

void led_update_ports(led_t led_state) {
    #ifdef CONSOLE_ENABLE
    uprintf("led_update_ports() caps=%2u, num=%2u\n", led_state.caps_lock, led_state.num_lock);
    #endif // CONSOLE_ENABLE


    #ifdef LED_NUM_LOCK_PIN
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    #ifdef CONSOLE_ENABLE
    uprintf("Layer %2u\n", layer);
    #endif // CONSOLE_ENABLE
    gpio_write_pin(LED_NUM_LOCK_PIN, ((led_state.num_lock || (layer == 1)) ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE) );
    #endif

    #ifdef LED_CAPS_LOCK_PIN
    gpio_write_pin(LED_CAPS_LOCK_PIN, (led_state.caps_lock ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE) );
    #endif

    // #ifdef LED_SCROLL_LOCK_PIN
    // gpio_write_pin(LED_SCROLL_LOCK_PIN, (led_state.scroll_lock ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE) );
    // #endif
}

bool led_update_user(led_t led_state) {
    // --- Sim. default ---

    led_update_ports(led_state);

    // --- Caffeine ---

    // #ifdef CAFFEINE_ENABLE
    // if (!led_update_caffeine(led_state, true, false)) return false;
    // #endif // CAFFEINE_ENABLE

    return false;  // don't allow default to run
}

#if defined(CAFFEINE_ENABLE)

void matrix_scan_user(void) {
    #ifdef CAFFEINE_ENABLE
    matrix_scan_caffeine();
    #endif // CAFFEINE_ENABLE
}

void housekeeping_task_user(void) {
    #ifdef CAFFEINE_ENABLE
    housekeeping_task_caffeine();
    #endif // CAFFEINE_ENABLE
}

#endif // CAFFEINE_ENABLE

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB red = adjust_to_brightness(RGB_RED, 64, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & 0x10) {
                rgb_matrix_set_color(i, red.r, red.g, red.b);
            }
        }
    }
    return false;
}

#endif // RGB_MATRIX_ENABLE

// Process keystrokes

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // #ifdef CONSOLE_ENABLE
    // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    // #endif // CONSOLE_ENABLE

    #ifdef KONAMI_ENABLE
    if (!process_record_konami_code(keycode, record)) { return false; }
    #endif // KONAMI_ENABLE

    #ifdef SOCD_CLEANER_ENABLE
    if (!process_socd_cleaner(keycode, record, &socd_ad)) { return false; }
    if (!process_socd_cleaner(keycode, record, &socd_ws)) { return false; }
    if (!process_socd_cleaner(keycode, record, &socd_ud)) { return false; }
    if (!process_socd_cleaner(keycode, record, &socd_lr)) { return false; }
    #endif // SOCD_CLEANER_ENABLE

    switch (keycode) {

        // --- macOS ---

        case QK_KB_0:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false;

        case QK_KB_1:
            if (record->event.pressed) {
                register_code(KC_LAUNCHPAD);
            } else {
                unregister_code(KC_LAUNCHPAD);
            }
            return false;

        case KC_SIRI:
            return kc_register_code_2(record, KC_LOPT, KC_SPACE);
            break;

        case KC_SCREEN_SHOT:
           return kc_register_code_3(record, KC_LSFT, KC_LCMD, KC_4);
           break;

        // --- Windows ---

        case KC_TASK_VIEW:
            return kc_register_code_2(record, KC_LWIN, KC_TAB);
            break;

        case KC_FILE_EXPLORER:
             return kc_register_code_2(record, KC_LWIN, KC_E);
             break;

        case KC_CORTANA:
            return kc_register_code_2(record, KC_LWIN, KC_C);
            break;

        // --- Other ---

        #ifdef CAFFEINE_ENABLE

        case KC_CAFFEINE_TOGGLE:
            return caffeine_process_toggle_keycode(record);
            break;

        case KC_CAFFEINE_ON:
            return caffeine_process_on_keycode(record);
            break;

        case KC_CAFFEINE_OFF:
            return caffeine_process_off_keycode(record);
            break;

        #endif // CAFFEINE_ENABLE

        #ifdef SOCD_CLEANER_ENABLE

        case KC_SOCD_ON:  // Turn SOCD Cleaner on.
            if (record->event.pressed) {
                socd_cleaner_enabled = true;
            }
            return false;

        case KC_SOCD_OFF:  // Turn SOCD Cleaner off.
            if (record->event.pressed) {
                socd_cleaner_enabled = false;
            }
            return false;

        case KC_SOCD_TOGGLE:  // Toggle SOCD Cleaner.
            if (record->event.pressed) {
                socd_cleaner_enabled = !socd_cleaner_enabled;
            }
            return false;

        #endif // SOCD_CLEANER_ENABLE

        case KC_VERSION:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            break;

        default:
          break;
    }

    return true;
}
