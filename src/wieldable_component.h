#ifndef WIELDABLE_COMPONENT
#define WIELDABLE_COMPONENT

#include "base_component.h"

typedef enum {
    WieldableNowhere    = 0,
    WieldableRightHand,
    WieldableLeftHand,
    WieldableBothHands,
} WieldablePosition;

struct WieldableComponent : public BaseComponent {
    int                 baseDamage;
    int                 baseDefence;
    WieldablePosition   position;
};

#endif
