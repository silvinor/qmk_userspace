/* (c) 2024 Silvino R. */
/* SPDX-License-Identifier: GPL-3.0-or-later */

#pragma once

#define DEBOUNCE 15 // default is 5, in ms

#define VIAL_KEYBOARD_UID {0x00, 0x33, 0xFA, 0x80, 0xFE, 0x45, 0x49, 0xD9}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* Sane Limits */
#define VIAL_TAP_DANCE_ENTRIES 4
#define VIAL_COMBO_ENTRIES 4
#define VIAL_KEY_OVERRIDE_ENTRIES 4
// #define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Override M2 crap    Top = A15, Middle = C10, Bottom = C11 */
#define LED_PIN_ON_STATE true
// #undef LED_CAPS_LOCK_PIN
// #define LED_CAPS_LOCK_PIN A15 // A15

// #undef LED_NUM_LOCK_PIN
// #define LED_NUM_LOCK_PIN  C10 // C10

#undef LED_SCROLL_LOCK_PIN  // disable Scroll Lock
#define LED_CAFFIENE_PIN  C11 // C11
