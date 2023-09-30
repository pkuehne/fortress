#pragma once

typedef enum {
    HUNGER = 0,
    THIRST = 1,
} HUNGER_THIRST;

typedef enum {
    HEALTH_EFFECT = 1,
} EFFECT;

struct ConsumableComponent {
    HUNGER_THIRST quenches;
    int quenchStrength;
    EFFECT effect;
    int effectStrength;
};