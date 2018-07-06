#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "../components/sprite_component.h"
#include "color.h"

enum class Material {
    None = 0,
    Grass = 1,
    Rock = 2,
};

class Floor {
public:
    explicit Floor(Material material);
    SpriteComponent& getSprite() { return m_sprite; }
    void setMaterial(Material material);

private:
    Material m_material;
    SpriteComponent m_sprite;
};

#endif
