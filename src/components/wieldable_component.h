#pragma once

#include "component_base.h"

typedef enum {
    WieldableNowhere = 0,
    WieldableRightHand,
    WieldableLeftHand,
    WieldableBothHands,
} WieldablePosition;

struct WieldableComponent : public ComponentBase {
    int baseDamage;
    int baseDefence;
    WieldablePosition position;
};

