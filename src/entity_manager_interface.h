#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class GameEngineInterface;

#include <vector>
#include "utility.h"
#include "tile.h"
#include "entity.h"

class EntityManagerInterface {
public:
    virtual ~EntityManagerInterface() { }

    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void destroy() = 0;

    virtual EntityId createEntity ( Location& location) = 0;
    virtual void addEntity (EntityId id, Location& location) = 0;
    virtual void destroyEntity (EntityId id) = 0;
    virtual EntityId getPlayer () = 0;
    virtual EntityId getMaxId() = 0;


    virtual EntityId createWallPrefab (Location& location)    = 0;
    virtual EntityId createPlayerPrefab (Location& location)  = 0;
    virtual EntityId createEnemyPrefab (Location& location)   = 0;
    virtual EntityId createTilePrefab (Location& location)    = 0;
    virtual EntityId createMarkerPrefab (Location& location)  = 0;
    virtual EntityId createStairPrefab (STAIR dir, Location& location)   = 0;
    virtual EntityId createWeaponPrefab () = 0;
    virtual EntityId createShieldPrefab () = 0;
    virtual EntityId createHelmetPrefab () = 0;

    virtual EntityHolder findEntitiesNear (unsigned int x, unsigned int y, unsigned radius) = 0;
    virtual EntityHolder findEntitiesAt (unsigned int x, unsigned int y) = 0;
    virtual EntityHolder findEntitiesToThe (DIRECTION a_direction, EntityId a_entity) = 0;

    virtual Location getLocation (EntityId entity) = 0;
    virtual void setLocation (EntityId entity, Location& location) = 0;
    virtual EntityHolder& get(unsigned int area = 0) = 0;
};

#endif
