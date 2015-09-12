#ifndef TILE_H
#define TILE_H

#include "entity.h"
#include <unordered_set>

typedef std::unordered_set<EntityId> EntityHolder;
typedef EntityHolder::iterator EntityIter;
typedef EntityHolder::const_iterator EntityConstIter;
class Tile {
public:
    unsigned int lastVisited;
    EntityHolder entities;
};

#endif
