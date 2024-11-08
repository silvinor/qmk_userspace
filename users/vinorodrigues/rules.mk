# Copyright 2023 Vino Rodrigues (@vinorodrigues)
# SPDX-License-Identifier: GPL-3.0-or-later

SRC += vinorodrigues_common.c

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif

ifeq ($(strip $(KONAMI_ENABLE)), yes)
    SRC += konami.c
    OPT_DEFS += -DKONAMI_ENABLE
endif

ifeq ($(strip $(SOCD_CLEANER_ENABLE)), yes)
    SRC += socd_cleaner.c
    OPT_DEFS += -DSOCD_CLEANER_ENABLE
endif
