#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class GameEngineInterface;

#include <component_manager.h>
#include <sprite_component.h>
#include <collider_component.h>
#include <health_component.h>
#include <description_component.h>
#include <player_component.h>
#include <npc_component.h>
#include <location_component.h>
#include <stair_component.h>
#include <equipment_component.h>
#include <wearable_component.h>
#include <wieldable_component.h>
#include <vector>
#include <utility.h>

class EntityManagerInterface {
public:
    virtual ~EntityManagerInterface() { }

    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void destroy() = 0;

    virtual EntityId createEntity () = 0;
    virtual void destroyEntity (EntityId id) = 0;
    virtual EntityId getPlayer () = 0;


    virtual EntityId createWallPrefab (unsigned int x, unsigned int y, unsigned int z=0)    = 0;
    virtual EntityId createPlayerPrefab (unsigned int x, unsigned int y, unsigned int z=0)  = 0;
    virtual EntityId createEnemyPrefab (unsigned int x, unsigned int y, unsigned int z=0)   = 0;
    virtual EntityId createTilePrefab (unsigned int x, unsigned int y, unsigned int z=0)    = 0;
    virtual EntityId createMarkerPrefab (unsigned int x, unsigned int y, unsigned int z=0)  = 0;
    virtual EntityId createStairPrefab (STAIR dir, unsigned int x, unsigned int y, unsigned int z=0)   = 0;
    virtual EntityId createWeaponPrefab () = 0;
    virtual EntityId createShieldPrefab () = 0;
    virtual EntityId createHelmetPrefab () = 0;

    virtual ComponentManagerInterface<SpriteComponent>*         getSprites()        = 0;
    virtual ComponentManagerInterface<ColliderComponent>*       getColliders()      = 0;
    virtual ComponentManagerInterface<HealthComponent>*         getHealths()        = 0;
    virtual ComponentManagerInterface<DescriptionComponent>*    getDescriptions()   = 0;
    virtual ComponentManagerInterface<PlayerComponent>*         getPlayers()        = 0;
    virtual ComponentManagerInterface<NpcComponent>*            getNpcs()           = 0;
    virtual ComponentManagerInterface<LocationComponent>*       getLocations()      = 0;
    virtual ComponentManagerInterface<StairComponent>*          getStairs()         = 0;
    virtual ComponentManagerInterface<EquipmentComponent>*      getEquipments()     = 0;
    virtual ComponentManagerInterface<WearableComponent>*       getWearables()      = 0;
    virtual ComponentManagerInterface<WieldableComponent>*      getWieldables()     = 0;

    virtual std::vector<EntityId> findEntitiesNear (unsigned int x, unsigned int y, unsigned radius) = 0;
    virtual std::vector<EntityId> findEntitiesAt (unsigned int x, unsigned int y) = 0;
    virtual std::vector<EntityId> findEntitiesToThe (DIRECTION a_direction, EntityId a_entity) = 0;

};

#endif
