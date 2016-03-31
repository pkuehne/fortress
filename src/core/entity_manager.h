#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "entity_manager_interface.h"
#include "utility.h"
#include <map>
#include <vector>

typedef std::map<EntityId, Location> LocationMap;
typedef LocationMap::const_iterator LocationConstIter;
typedef LocationMap::iterator LocationIter;

class EntityManager : public EntityManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void destroy() {}

    EntityId createEntity (Location& location);
    void addEntity (EntityId id, Location& location);
    void destroyEntity (EntityId);
    EntityId getPlayer ();
    EntityId getMaxId() { return m_maxId; }

    EntityId createWallPrefab (Location& location);
    EntityId createPlayerPrefab (Location& location);
    EntityId createEnemyPrefab (Location& location);
    EntityId createTrollPrefab (Location& location);
    EntityId createMarkerPrefab (Location& location);
    EntityId createStairPrefab (STAIR dir, Location& location);
    EntityId createWeaponPrefab (Location& location);
    EntityId createShieldPrefab (Location& location);
    EntityId createHelmetPrefab (Location& location);
    EntityId createPotionPrefab (Location& location);
    EntityId createTreePrefab(Location& location);
    EntityId createCorpsePrefab(Location& location, char sprite);

    Location getLocation (EntityId entity) { return m_locations[entity]; }
    void setLocation (EntityId entity, Location& location);

    bool validLocation (Location& location);

    EntityHolder& get(unsigned int area = 0);
private:
    GameEngineInterface*                m_engine;
    unsigned long                       m_maxId;
    EntityId                            m_player;
    LocationMap                         m_locations;
    std::map<unsigned int, EntityHolder> m_entities;
};

#endif
