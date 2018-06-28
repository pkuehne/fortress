#ifndef TILE_H
#define TILE_H

#include "entity.h"
#include "floor.h"

class Tile {
public:
    Tile() : m_floor(Material::Grass), m_entities(), m_lit(false) {}
    unsigned int lastVisited = 0;
    bool& lit() { return m_lit; }
    const EntityHolder& entities() { return m_entities; }
    void addEntity(EntityId entity) { m_entities.insert(entity); }
    void removeEntity(EntityId entity) { m_entities.erase(entity); }
    Floor& getFloor() { return m_floor; }

private:
    Floor m_floor;
    EntityHolder m_entities;
    bool m_lit;
};

#endif
