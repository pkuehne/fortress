#include "entity_manager.h"
#include "gameengine.h"
#include <fstream>
#include <iostream>

void EntityManager::initialise (GameEngineInterface* engine)
{
    maxId = 0;
    m_engine = engine;
}

void EntityManager::destroy ()
{

}

Entity* EntityManager::createEntity (const std::string& name) {
    Entity* l_entity = new Entity();
    l_entity->setId (maxId++);
    l_entity->setName (name);
    m_idMap[l_entity->getId()]     = l_entity;
    m_nameMap[l_entity->getName()]   = l_entity;

    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = l_entity;
    m_engine->raiseEvent (l_event);

    return l_entity;
}

Entity* EntityManager::getEntity (std::string name) {
    std::map<std::string, Entity*>::iterator it = m_nameMap.find (name);
    if (it == m_nameMap.end()) return 0;
    return it->second;
}

Entity* EntityManager::getEntity (EntityId id) {
    std::map<EntityId, Entity*>::iterator it = m_idMap.find (id);
    if (it == m_idMap.end()) return 0;
    return it->second;
}

Entity* EntityManager::createWallPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Wall");

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 247;
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);

    //Collider Component
    ColliderComponent l_collider;
    getColliders().add (l_entity, l_collider);

    return l_entity;
}

Entity* EntityManager::createPlayerPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Player");

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '@';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);


    //Collider Component
    ColliderComponent l_collider;
    getColliders().add (l_entity, l_collider);

    return l_entity;
}

Entity* EntityManager::createEnemyPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Enemy");

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'O';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);

    //Collider Component
    ColliderComponent l_collider;
    getColliders().add (l_entity, l_collider);

    return l_entity;
}

Entity* EntityManager::createTilePrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Tile");

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '.';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites().add (l_entity, l_sprite);

    return l_entity;
}
