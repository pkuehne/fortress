#pragma once

#include "../core/color.h"
#include "component_base.h"

struct SpriteComponent {
    unsigned int sprite = 0;
    unsigned int renderLayer = 1;
    Color fgColor;
    Color bgColor;
};
