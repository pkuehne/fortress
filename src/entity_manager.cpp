#include "entity_manager.h"
#include "gameengine.h"
#include <fstream>
#include <iostream>

void EntityManager::initialise (GameEngineInterface* engine)
{
    maxId = 0;
    m_engine = engine;
    m_player = 0;
}

Entity* EntityManager::createEntity (const std::string& name) {
    Entity* l_entity = new Entity();
    l_entity->setId (maxId++);
    l_entity->setName (name);
    m_idMap[l_entity->getId()]     = l_entity;
    m_nameMap[l_entity->getName()]   = l_entity;

    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = l_entity->getId();
    m_engine->raiseEvent (l_event);

    return l_entity;
}

void EntityManager::destroyEntity (EntityId id) {
    std::map<EntityId, Entity*>::iterator it = m_idMap.find (id);
    if (it == m_idMap.end()) return;

    getColliders()->remove (it->second);
    getSprites()->remove (it->second);
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = it->second->getId();
    m_engine->raiseEvent (l_event);

    m_idMap.erase (it);
}


Entity* EntityManager::getPlayer () {
    if (m_player == 0) {
        std::map<EntityId, Entity*>::iterator it = m_idMap.begin();
        for (; it != m_idMap.end(); it++) {
            if (it->second->hasTag(PLAYER)) {
                m_player = it->second;
            }
        }
    }
    return m_player;
}


Entity* EntityManager::getEntity (EntityId id) {
    std::map<EntityId, Entity*>::iterator it = m_idMap.find (id);
    if (it == m_idMap.end()) return 0;
    return it->second;
}

Entity* EntityManager::createWallPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Wall");
    l_entity->addTag (WALL);
    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'W';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity, l_sprite);

    //Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

    return l_entity;
}

Entity* EntityManager::createPlayerPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Player");
    l_entity->addTag (PLAYER);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '@';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity, l_sprite);


    //Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

    return l_entity;
}

Entity* EntityManager::createEnemyPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Orc");
    l_entity->addTag (MONSTER);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'O';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity, l_sprite);

    //Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

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
    getSprites()->add (l_entity, l_sprite);

    return l_entity;
}
