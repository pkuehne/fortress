#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "component_manager.h"
#include "sprite_component.h"
#include "collider_component.h"
#include <map>

class EntityManager {
public:
    void initialise();
    void destroy();

    Entity* createEntity (const std::string& name = "empty");

    void createWallPrefab (unsigned int x, unsigned int y);
    void createPlayerPrefab (unsigned int x, unsigned int y);
    void createEnemyPrefab (unsigned int x, unsigned int y);
    void createTilePrefab (unsigned int x, unsigned int y);

    ComponentManager<SpriteComponent>& getSprites() { return m_sprites; }
    ComponentManager<ColliderComponent>& getColliders() { return m_colliders; }
    Entity* getEntity (std::string name);
    Entity* getEntity (EntityId id);

private:
    unsigned long                       maxId;
    std::map<EntityId, Entity*>         m_idMap;
    std::map<std::string, Entity*>      m_nameMap;
    ComponentManager<SpriteComponent>   m_sprites;
    ComponentManager<ColliderComponent> m_colliders;

};

#endif
