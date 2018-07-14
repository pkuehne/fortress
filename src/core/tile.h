#pragma once

#include "../components/sprite_component.h"
#include "entity.h"

enum class FloorMaterial {
    None = 0,
    Grass = 1,
    Rock = 2,
};

enum class WallMaterial {
    None = 0,
    Rock = 1,
};

class Tile {
public:
    Tile() = default;
    ~Tile() = default;

    bool& lit() { return m_lit; }
    bool lit() const { return m_lit; }

    unsigned int& lastVisited() { return m_lastVisited; }
    unsigned int lastVisited() const { return m_lastVisited; }

    bool blocked() const { return m_wallMaterial != WallMaterial::None; }

    const EntityHolder& entities() { return m_entities; }
    void addEntity(EntityId entity) { m_entities.insert(entity); }
    void removeEntity(EntityId entity) { m_entities.erase(entity); }

    void setFloorMaterial(const FloorMaterial& material);
    FloorMaterial getFloorMaterial() const { return m_floorMaterial; }
    void setWallMaterial(const WallMaterial& material);
    WallMaterial getWallMaterial() const { return m_wallMaterial; }

    void overrideSpriteSymbol(const char symbol) { m_sprite.sprite = symbol; }
    const SpriteComponent& getSprite() const { return m_sprite; }

private:
    void setSprite();

private:
    FloorMaterial m_floorMaterial = FloorMaterial::None;
    WallMaterial m_wallMaterial = WallMaterial::None;
    SpriteComponent m_sprite;

    EntityHolder m_entities;
    bool m_lit = false;
    unsigned int m_lastVisited = 0;
};
