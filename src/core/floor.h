#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "color.h"
#include "sprite_component.h"

typedef enum {
    None        = 0,
    Grass       = 1,
    Rock        = 2,
} Material;

class Floor {
public:
    Floor (Material material);
    SpriteComponent& getSprite() { return m_sprite; }
    void setMaterial(Material material);
private:
    Material        m_material;
    SpriteComponent m_sprite;
};

#endif
