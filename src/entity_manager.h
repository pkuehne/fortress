#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "component_manager_interface.h"
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
    void destroyEntity (EntityId);
    EntityId getPlayer ();

    EntityId createWallPrefab (Location& location);
    EntityId createPlayerPrefab (Location& location);
    EntityId createEnemyPrefab (Location& location);
    EntityId createTilePrefab (Location& location);
    EntityId createMarkerPrefab (Location& location);
    EntityId createStairPrefab (STAIR dir, Location& location);
    EntityId createWeaponPrefab ();
    EntityId createShieldPrefab ();
    EntityId createHelmetPrefab ();

    ComponentManagerInterface<SpriteComponent>* getSprites() { return &m_sprites; }
    ComponentManagerInterface<ColliderComponent>* getColliders() { return &m_colliders; }
    ComponentManagerInterface<HealthComponent>* getHealths() { return &m_healths; }
    ComponentManagerInterface<DescriptionComponent>* getDescriptions() { return &m_descriptions; }
    ComponentManagerInterface<PlayerComponent>* getPlayers() { return &m_players; }
    ComponentManagerInterface<NpcComponent>* getNpcs() { return &m_npcs; }
    ComponentManagerInterface<LocationComponent>* getLocations() { return &m_location; }
    ComponentManagerInterface<StairComponent>* getStairs() { return &m_stairs; }
    ComponentManagerInterface<EquipmentComponent>* getEquipments() { return &m_equipments; }
    ComponentManagerInterface<WearableComponent>* getWearables() { return &m_wearables; }
    ComponentManagerInterface<WieldableComponent>* getWieldables() { return &m_wieldables; }
    ComponentManagerInterface<DroppableComponent>* getDroppables() { return &m_droppables; }

    std::vector<EntityId> findEntitiesNear (unsigned int x, unsigned int y, unsigned radius);
    std::vector<EntityId> findEntitiesAt (unsigned int x, unsigned int y);
    std::vector<EntityId> findEntitiesToThe (DIRECTION a_direction, EntityId a_entity);

    Location getLocation (EntityId entity) { return m_locations[entity]; }
    void setLocation (EntityId entity, Location& location);

private:
    GameEngineInterface*                m_engine;
    unsigned long                       maxId;
    EntityId                            m_player;

    //std::map<EntityId, Entity*>         m_idMap;

    ComponentManager<SpriteComponent>       m_sprites;
    ComponentManager<ColliderComponent>     m_colliders;
    ComponentManager<HealthComponent>       m_healths;
    ComponentManager<DescriptionComponent>  m_descriptions;
    ComponentManager<PlayerComponent>       m_players;
    ComponentManager<NpcComponent>          m_npcs;
    ComponentManager<LocationComponent>     m_location;
    ComponentManager<StairComponent>        m_stairs;
    ComponentManager<EquipmentComponent>    m_equipments;
    ComponentManager<WearableComponent>     m_wearables;
    ComponentManager<WieldableComponent>    m_wieldables;
    ComponentManager<DroppableComponent>    m_droppables;

    LocationMap m_locations;

};

#endif
