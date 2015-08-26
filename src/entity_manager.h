#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "component_manager_interface.h"
#include "entity_manager_interface.h"
#include <map>
#include "sprite_component.h"
#include "collider_component.h"
#include "health_component.h"
#include "description_component.h"
#include "utility.h"
#include <vector>

class EntityManager : public EntityManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void destroy() {}

    EntityId createEntity ();
    void destroyEntity (EntityId);
    EntityId getPlayer ();

    EntityId createWallPrefab (unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createPlayerPrefab (unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createEnemyPrefab (unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createTilePrefab (unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createMarkerPrefab (unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createStairPrefab (STAIR dir, unsigned int x, unsigned int y, unsigned int z=0);
    EntityId createWeaponPrefab ();
    EntityId createShieldPrefab ();
    EntityId createHelmetPrefab ();
    
    ComponentManagerInterface<SpriteComponent>* getSprites() { return &m_sprites; }
    ComponentManagerInterface<ColliderComponent>* getColliders() { return &m_colliders; }
    ComponentManagerInterface<HealthComponent>* getHealths() { return &m_healths; }
    ComponentManagerInterface<DescriptionComponent>* getDescriptions() { return &m_descriptions; }
    ComponentManagerInterface<PlayerComponent>* getPlayers() { return &m_players; }
    ComponentManagerInterface<NpcComponent>* getNpcs() { return &m_npcs; }
    ComponentManagerInterface<LocationComponent>* getLocations() { return &m_locations; }
    ComponentManagerInterface<StairComponent>* getStairs() { return &m_stairs; }
    ComponentManagerInterface<EquipmentComponent>* getEquipments() { return &m_equipments; }
    ComponentManagerInterface<WearableComponent>* getWearables() { return &m_wearables; }
    ComponentManagerInterface<WieldableComponent>* getWieldables() { return &m_wieldables; }

    std::vector<EntityId> findEntitiesNear (unsigned int x, unsigned int y, unsigned radius);
    std::vector<EntityId> findEntitiesAt (unsigned int x, unsigned int y);
    std::vector<EntityId> findEntitiesToThe (DIRECTION a_direction, EntityId a_entity);


private:
    GameEngineInterface*                m_engine;
    unsigned long                       maxId;
    EntityId                            m_player;

    std::map<EntityId, Entity*>         m_idMap;

    ComponentManager<SpriteComponent>       m_sprites;
    ComponentManager<ColliderComponent>     m_colliders;
    ComponentManager<HealthComponent>       m_healths;
    ComponentManager<DescriptionComponent>  m_descriptions;
    ComponentManager<PlayerComponent>       m_players;
    ComponentManager<NpcComponent>          m_npcs;
    ComponentManager<LocationComponent>     m_locations;
    ComponentManager<StairComponent>        m_stairs;
    ComponentManager<EquipmentComponent>    m_equipments;
    ComponentManager<WearableComponent>     m_wearables;
    ComponentManager<WieldableComponent>    m_wieldables;
};

#endif
