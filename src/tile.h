#ifndef TILE_H
#define TILE_H

#include "entity.h"
#include <vector>

class Tile {
public:
    bool isVisible;
    bool isRevealed;
    std::vector<EntityId> entities;
};

#endif
