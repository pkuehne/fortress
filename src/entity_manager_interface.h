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

    virtual Entity* createEntity (const std::string& name = "empty") = 0;

    virtual Entity* createWallPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createPlayerPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createEnemyPrefab (unsigned int x, unsigned int y) = 0;
    virtual Entity* createTilePrefab (unsigned int x, unsigned int y) = 0;

    virtual ComponentManager<SpriteComponent>& getSprites() = 0;
    virtual ComponentManager<ColliderComponent>& getColliders() = 0;
    virtual Entity* getEntity (std::string name) = 0;
    virtual Entity* getEntity (EntityId id) = 0;

};

#endif
