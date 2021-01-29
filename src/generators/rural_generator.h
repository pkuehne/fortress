#pragma once

#include "../core/entity.h"
#include "generator_interface.h"
#include <string>
#include <vector>

class Location;

class RuralGenerator : public GeneratorInterface {
public:
    bool generate() override;
    void reset() override;
    void createEntitiesFromMap() override;
    std::vector<EntityId>& getAreaLinks() { return m_areaLinks; }
    EntityId createPrefab(const std::string& type, const Location& location);

private:
    void placeWoods();
    void placeDungeonStairs();
    void placeForester();
    void placePlayer();
    void placeApples();

private:
    std::vector<EntityId> m_areaLinks;
};
