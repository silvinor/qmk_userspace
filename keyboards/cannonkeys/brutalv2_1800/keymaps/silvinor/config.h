// Copyright 2023 Silvino R. (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#ifdef FORCE_NKRO
#    undef FORCE_NKRO
#endif
#ifdef NKRO_ENABLE
#    undef NKRO_ENABLE
#endif

/* VIA keymap layers */

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#    undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Tap Code */
#define TAPPING_TERM 100
#define PERMISSIVE_HOLD
#define TAP_CODE_DELAY 10

/* correct for over sensitive keys */
#ifdef DEBOUNCE
#    undef DEBOUNCE
#endif
#define DEBOUNCE 10

/* bigger wear leveling buffer */
#define WEAR_LEVELING_LOGICAL_SIZE 4096
#define WEAR_LEVELING_BACKING_SIZE 8192

/* Some new & add-on features not technically needed */
#define SERIAL_NUMBER_USE_HARDWARE_ID true
#define MATRIX_MASKED true

/* Switch off upstream LED sets so that we can manually control these */
#undef LED_CAPS_LOCK_PIN
#undef LED_NUM_LOCK_PIN
#define PWM_CAPS_LOCK_PIN GP29
#define PWM_NUM_LOCK_PIN GP2

#define LED_CAFFEINE_PIN PWM_CAPS_LOCK_PIN
#define LED_CAFFEINE_SHARED

/* Vial stuff */

// #define VIAL_KEYBOARD_UID {0x37, 0xF9, 0x90, 0xEC, 0x99, 0xE6, 0x0A, 0x16}
// #define VIAL_UNLOCK_COMBO_ROWS {0, 3}
// #define VIAL_UNLOCK_COMBO_COLS {0, 13}
