# How to use the Caffeine mod

## In your keymap `rules.mk`

### Add the path and source

```make
CAFFEINE_ENABLE = yes

# VPATH += $(QMK_USERSPACE)/users/silvinor

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif
```

## In your `keymap.c` file do:

### Include the `.h` file

```c
#include "caffeine.h"
```

### Define a user keycode

```c
#define KC_CAFFEINE_TOGGLE QK_KB_9  // 9 can be anything sane
```

or as enum

```c
enum {
    KC_XXX = QK_KB_0,
    KC_YYY,
    KC_ZZZ,
    // ...
    KC_CAFFEINE_TOGGLE
};
```

### If you're using `RGB_MATRIX`, modify the RGB functions

#### `rgb_matrix_indicators_user`

```c
bool rgb_matrix_indicators_user(void) {
    // ...
    if (!rgb_matrix_indicators_caffeine()) return false;
    // ...
    return true;
}
```

#### ~~`led_update_user`~~

***[REMOVED!]*** <!-- FIXME : DOcs -->

```c
bool led_update_user(led_t led_state) {
    // ...
    if (!led_update_caffeine(led_state)) return false;
    // ...
    return true;
}
```

### Modify the scan and housekeeping functions

#### `matrix_scan_user`

```c
void matrix_scan_user(void) {
    // ...
    matrix_scan_caffeine();
    // ...
}
```

#### `housekeeping_task_user`

```c
void housekeeping_task_user(void) {
    // ...
    housekeeping_task_caffeine();
    // ...
}
```

### Finally, call the process key method

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case abc: ...

        case KC_CAFFEINE_TOGGLE:
          return caffeine_process_toggle_keycode(record);
          break;
        
        // case xyz: ...

        default: 
          break;
    }
    return true;
}
```

---
:heart: **Vino**
