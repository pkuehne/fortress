#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "component_manager.h"
#include "sprite_component.h"
#include "collider_component.h"
#include "entity_manager_interface.h"
#include <map>

class EntityManager : public EntityManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void destroy() {}

    Entity* createEntity (const std::string& name = "empty");

    Entity* createWallPrefab (unsigned int x, unsigned int y);
    Entity* createPlayerPrefab (unsigned int x, unsigned int y);
    Entity* createEnemyPrefab (unsigned int x, unsigned int y);
    Entity* createTilePrefab (unsigned int x, unsigned int y);

    ComponentManager<SpriteComponent>& getSprites() { return m_sprites; }
    ComponentManager<ColliderComponent>& getColliders() { return m_colliders; }
    Entity* getEntity (std::string name);
    Entity* getEntity (EntityId id);

private:
    GameEngineInterface*                m_engine;
    unsigned long                       maxId;
    std::map<EntityId, Entity*>         m_idMap;
    std::map<std::string, Entity*>      m_nameMap;
    ComponentManager<SpriteComponent>   m_sprites;
    ComponentManager<ColliderComponent> m_colliders;

};

#endif
