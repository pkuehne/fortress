#pragma once

#include "../core/entity.h"
#include "generator_interface.h"
#include <vector>

class RuralGenerator : public GeneratorInterface {
public:
    bool generate();
    void reset();
    void createEntitiesFromMap();
    std::vector<EntityId>& getAreaLinks() { return m_areaLinks; }

private:
    void placeWoods();
    void placeDungeonStairs();
    void placeForester();
    void placePlayer();
    void placeApples();

private:
    std::vector<EntityId> m_areaLinks;
};
