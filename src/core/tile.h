#ifndef TILE_H
#define TILE_H

#include "entity.h"

class Tile {
public:
    unsigned int lastVisited = 0;
    EntityHolder entities;
};

#endif
