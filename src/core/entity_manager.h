#pragma once

#include "../core/component_manager.h"
#include "../core/event_manager.h"
#include "../core/map_manager.h"
#include "entity.h"
#include "location.h"
#include "utility.h"
#include <map>
#include <memory>
#include <vector>

typedef std::map<EntityId, Location> LocationMap;
typedef LocationMap::const_iterator LocationConstIter;
typedef LocationMap::iterator LocationIter;

class EntityManager {
public:
    EntityManager() = default;
    virtual ~EntityManager() = default;

    void initialise(std::shared_ptr<EventManager> events) { m_events = events; }
    void destroy() {}

    virtual EntityId createEntity(const Location& location);
    virtual void addEntity(EntityId id, const Location& location);
    virtual void destroyEntity(EntityId);
    virtual EntityId getMaxId() { return m_maxId; }

    virtual Location getLocation(EntityId entity) {
        return m_locations[entity];
    }
    virtual void setLocation(EntityId entity, const Location& location);

    virtual EntityHolder& get(unsigned int area) { return m_entities[area]; }
    virtual EntityHolder& all() { return m_allEntities; }
    virtual unsigned int count() { return m_locations.size(); }

private:
    std::shared_ptr<EventManager> m_events;

    unsigned long m_maxId = 1;
    EntityId m_player = 0;
    LocationMap m_locations;
    EntityHolder m_allEntities;
    std::map<unsigned int, EntityHolder> m_entities;
};