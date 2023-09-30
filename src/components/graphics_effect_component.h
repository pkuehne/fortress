#pragma once

#include "../core/color.h"

typedef enum {
    EFFECT_NONE = 0,
    EFFECT_BLINK_SLOW,
    EFFECT_BLINK_FAST,
    EFFECT_CHANGE_COLOR,
    EFFECT_MAX
} GRAPHICS_EFFECT;

struct GraphicsEffectComponent {
    unsigned int ticks = 0;
    unsigned int duration = 0;
    unsigned int org_tile = 0;
    GRAPHICS_EFFECT type = EFFECT_NONE;
    bool removeEntity = false;
    Color org_color;
    Color new_color;
};
