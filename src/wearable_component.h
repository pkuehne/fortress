#ifndef WEARABLE_COMPONENT
#define WEARABLE_COMPONENT

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

struct WearableComponent {
    int                 baseDamageAbsorb;
    WearablePosition    position;
    int                 warmth;
};

#endif
