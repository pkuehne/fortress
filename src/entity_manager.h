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

class EntityManager : public EntityManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void destroy() {}

    Entity* createEntity (const std::string& name);
    void destroyEntity (EntityId);
    Entity* getPlayer ();

    Entity* createWallPrefab (unsigned int x, unsigned int y);
    Entity* createPlayerPrefab (unsigned int x, unsigned int y);
    Entity* createEnemyPrefab (unsigned int x, unsigned int y);
    Entity* createTilePrefab (unsigned int x, unsigned int y);

    ComponentManagerInterface<SpriteComponent>* getSprites() { return &m_sprites; }
    ComponentManagerInterface<ColliderComponent>* getColliders() { return &m_colliders; }
    ComponentManagerInterface<HealthComponent>* getHealths() { return &m_healths; }
    ComponentManagerInterface<DescriptionComponent>* getDescriptions() { return &m_descriptions; }

    Entity* getEntity (EntityId id);

private:
    GameEngineInterface*                m_engine;
    unsigned long                       maxId;
    Entity*                             m_player;
    std::map<EntityId, Entity*>         m_idMap;
    std::map<std::string, Entity*>      m_nameMap;
    ComponentManager<SpriteComponent>   m_sprites;
    ComponentManager<ColliderComponent> m_colliders;
    ComponentManager<HealthComponent>   m_healths;
    ComponentManager<DescriptionComponent>  m_descriptions;
};

#endif
