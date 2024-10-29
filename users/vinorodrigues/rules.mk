# Copyright 2023 Vino Rodrigues (@vinorodrigues)
# SPDX-License-Identifier: GPL-3.0-or-later

# Enable Mouse Keys
MOUSEKEY_ENABLE = no

# ----- My stuff ------

VPATH += $(QMK_USERSPACE)/users/vinorodrigues

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif

ifeq ($(strip $(KONAMI_ENABLE)), yes)
    SRC += konami.c
    OPT_DEFS += -DKONAMI_ENABLE
endif
