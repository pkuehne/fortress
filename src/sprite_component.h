#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "color.h"

struct SpriteComponent
{
    Color           fgColor;
    Color           bgColor;
    unsigned int    sprite;
};

#endif
