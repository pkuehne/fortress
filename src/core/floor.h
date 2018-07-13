#pragma once

#include "../components/sprite_component.h"

enum class Material {
    None = 0,
    Grass = 1,
    Rock = 2,
};

class Floor {
public:
    Floor() = default;
    explicit Floor(Material material);
    const SpriteComponent& getSprite() const { return m_sprite; }
    void setMaterial(Material material);
    Material getMaterial() const { return m_material; }

private:
    Material m_material = Material::None;
    SpriteComponent m_sprite;
};
