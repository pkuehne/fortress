#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

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
    void initialise(GameEngine* engine);
    void destroy() {}

    EntityId createEntity(Location& location);
    void addEntity(EntityId id, Location& location);
    void destroyEntity(EntityId);
    EntityId getPlayer();
    EntityId getMaxId() { return m_maxId; }

    Location getLocation(EntityId entity) { return m_locations[entity]; }
    void setLocation(EntityId entity, Location& location);

    bool validLocation(Location& location);

    EntityHolder& get(unsigned int area = 0);

private:
    GameEngine* m_engine;
    unsigned long m_maxId;
    EntityId m_player;
    LocationMap m_locations;
    std::map<unsigned int, EntityHolder> m_entities;
};

#endif
