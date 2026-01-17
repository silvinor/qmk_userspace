# Copyright 2022 Silvino R. (@silvinor)
# SPDX-License-Identifier: GPL-3.0-or-later

VIA_ENABLE = yes
# VIAL_ENABLE = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

# I don't like mayonnaise!
KEYBOARD_SHARED_EP = yes
NKRO_ENABLE = no
OPT_DEFS += -DNKRO_ENABLE
