#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "color.h"
#include "base_component.h"
struct SpriteComponent : public BaseComponent {
    Color           fgColor;
    Color           bgColor;
    unsigned int    sprite;
};

#endif
