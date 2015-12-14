#ifndef TILE_H
#define TILE_H

#include "entity.h"

class Tile {
public:
    unsigned int lastVisited = 0;
    const EntityHolder& entities() { return m_entities; }
    void addEntity (EntityId entity) { m_entities.insert (entity); }
    void removeEntity (EntityId entity) { m_entities.erase (entity); }
private:
    EntityHolder m_entities;
};

#endif
