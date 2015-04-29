#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "entity.h"
#include "component_manager.h"
#include "sprite_component.h"
#include "collider_component.h"

class EntityManager {
public:
    void initialise();
    void destroy();

    //Entity& getEntity (unsigned long id) { return m_entities[id]; }
    //void addEntity (Entity& entity);

    //void loadEntities ();
    Entity createEntity () { return maxId++; }

    void createWallEntity (unsigned int x, unsigned int y);
    void createPlayerEntity (unsigned int x, unsigned int y);
    void createEnemyEntity (unsigned int x, unsigned int y);
    void createRoom (unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd);

    ComponentManager<SpriteComponent>& getSprites() { return m_sprites; }
    ComponentManager<ColliderComponent>& getColliders() { return m_colliders; }
private:
    unsigned long   maxId;
    ComponentManager<SpriteComponent>   m_sprites;
    ComponentManager<ColliderComponent> m_colliders;

};

#endif
