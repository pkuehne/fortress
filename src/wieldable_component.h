#ifndef WIELDABLE_COMPONENT
#define WIELDABLE_COMPONENT

typedef enum {
    WieldableNowhere    = 0,
    WieldableRightHand,
    WieldableLeftHand,
    WieldableBothHands,
} WieldablePosition;

struct WieldableComponent {
    int                 baseDamage;
    WieldablePosition   position;
};

#endif
