#pragma once

#include "entity.h"
#include "location.h"
#include "utility.h"
#include <map>
#include <vector>

class GameEngine;

typedef std::map<EntityId, Location> LocationMap;
typedef LocationMap::const_iterator LocationConstIter;
typedef LocationMap::iterator LocationIter;

class EntityManager {
public:
    EntityManager() = default;
    virtual ~EntityManager() = default;

    void initialise(GameEngine* engine);
    void destroy() {}

    virtual EntityId createEntity(const Location& location);
    virtual void addEntity(EntityId id, const Location& location);
    virtual void destroyEntity(EntityId);
    virtual EntityId getPlayer();
    virtual EntityId getMaxId() { return m_maxId; }

    virtual Location getLocation(EntityId entity) {
        return m_locations[entity];
    }
    virtual void setLocation(EntityId entity, const Location& location);

    virtual EntityHolder& get(unsigned int area) { return m_entities[area]; }
    virtual EntityHolder& all() { return m_allEntities; }
    virtual unsigned int count() { return m_locations.size(); }

private:
    GameEngine* m_engine = nullptr;
    unsigned long m_maxId = 0;
    EntityId m_player = 0;
    LocationMap m_locations;
    EntityHolder m_allEntities;
    std::map<unsigned int, EntityHolder> m_entities;
};