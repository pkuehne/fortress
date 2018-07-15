#pragma once

#include "entity.h"
#include "entity_manager_interface.h"
#include "location.h"
#include "utility.h"
#include <map>
#include <vector>

class GameEngine;

typedef std::map<EntityId, Location> LocationMap;
typedef LocationMap::const_iterator LocationConstIter;
typedef LocationMap::iterator LocationIter;

class EntityManager { //: public EntityManagerInterface {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void initialise(GameEngine* engine);
    void destroy() {}

    EntityId createEntity(const Location& location);
    void addEntity(EntityId id, const Location& location);
    void destroyEntity(EntityId);
    EntityId getPlayer();
    EntityId getMaxId() { return m_maxId; }

    Location getLocation(EntityId entity) { return m_locations[entity]; }
    void setLocation(EntityId entity, Location& location);

    EntityHolder& get(unsigned int area) { return m_entities[area]; }
    unsigned int count() { return m_locations.size(); }

private:
    GameEngine* m_engine = nullptr;
    unsigned long m_maxId = 0;
    EntityId m_player = 0;
    LocationMap m_locations;
    std::map<unsigned int, EntityHolder> m_entities;
};