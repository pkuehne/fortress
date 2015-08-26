#ifndef WEARABLE_COMPONENT
#define WEARABLE_COMPONENT

typedef enum {
    WearableNowhere     = 0,
    WearableRightHand,
    WearableLeftHand,
    WearableRightArm,
    WearableLeftArm,
    WearableHead,
    WearableFace,
    WearableTorso,
    WearableChest,
    WearableLowerBody,
    WearableRightLeg,
    WearableLeftLeg,
    WearableRightFoot,
    WearableLeftFoot
} WearablePosition;

struct WearableComponent {
    int                 baseDamageAbsorb;
    WearablePosition    position;
};

#endif
