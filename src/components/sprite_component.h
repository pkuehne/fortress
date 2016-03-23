#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "color.h"
#include "component_base.h"

struct SpriteComponent : public ComponentBase {
    Color           fgColor;
    Color           bgColor;
    unsigned int    sprite;
    unsigned int    renderLayer = 1;
};

#endif
