#ifndef WEARABLE_COMPONENT
#define WEARABLE_COMPONENT

#include "base_component.h"

typedef enum {
    WearableNowhere     = 0,
    WearableHands,
    WearableArms,
    WearableHead,
    WearableFace,
    WearableChest,
    WearableLegs,
    WearableFeet
} WearablePosition;

struct WearableComponent : public BaseComponent {
    int                 baseDamageAbsorb;
    WearablePosition    position;
    int                 warmth;
};

#endif
