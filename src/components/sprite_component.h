#pragma once

#include "../core/color.h"
#include "component_base.h"

struct SpriteComponent : public ComponentBase {
    Color fgColor;
    Color bgColor;
    unsigned int sprite = 0;
    unsigned int renderLayer = 1;
};
