#ifndef WEARABLE_COMPONENT
#define WEARABLE_COMPONENT

#include "component_base.h"

typedef enum {
    WearableNowhere = 0,
    WearableHands,
    WearableArms,
    WearableHead,
    WearableFace,
    WearableChest,
    WearableLegs,
    WearableFeet
} WearablePosition;

struct WearableComponent : public ComponentBase {
    int baseDamageAbsorb;
    WearablePosition position;
    int warmth;
};

#endif
