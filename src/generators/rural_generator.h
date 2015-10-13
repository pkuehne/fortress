#ifndef RURAL_GENERATOR
#define RURAL_GENERATOR

#include "generator_interface.h"
#include "entity.h"
#include <vector>

class RuralGenerator : public GeneratorInterface {
public:
    bool generate();
    void reset();
    void createEntitiesFromMap();
    std::vector<EntityId>& getAreaLinks () { return m_areaLinks; }
private:
    void placeWoods();
    void placeDungeonStairs();
    void placePlayer();

private:
    std::vector<EntityId> m_areaLinks;
};

#endif
