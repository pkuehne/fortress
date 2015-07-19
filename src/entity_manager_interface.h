#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

class GameEngineInterface;
class Entity;
#include <component_manager.h>
#include <sprite_component.h>
#include <collider_component.h>

class EntityManagerInterface {
public:
    virtual ~EntityManagerInterface() { }

    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void destroy() = 0;

    virtual Entity* createEntity (const std::string& name) = 0;
    virtual void destroyEntity (EntityId id) = 0;
    virtual Entity* getPlayer () = 0;


    virtual Entity* createWallPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createPlayerPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createEnemyPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createTilePrefab (unsigned int x, unsigned int y) = 0;

    virtual ComponentManagerInterface<SpriteComponent>* getSprites() = 0;
    virtual ComponentManagerInterface<ColliderComponent>* getColliders() = 0;
    virtual Entity* getEntity (EntityId id) = 0;

};

#endif
