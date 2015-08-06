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

    getColliders()->remove (it->second->getId());
    getSprites()->remove (it->second->getId());
    getHealths()->remove (it->second->getId());
    getDescriptions()->remove (it->second->getId());
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = it->second->getId();
    m_engine->raiseEvent (l_event);

    m_idMap.erase (it);
}


EntityId EntityManager::getPlayer () {
    if (m_player == 0) {
        std::map<EntityId, Entity*>::iterator it = m_idMap.begin();
        for (; it != m_idMap.end(); it++) {
            if (it->second->hasTag(PLAYER)) {
                m_player = it->first;
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
    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'W';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity->getId(), l_sprite);

    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity->getId(), l_collider);

    DescriptionComponent l_description;
    l_description.title = "Wall";
    l_description.text = "A smooth granite wall";
    getDescriptions()->add (l_entity->getId(), l_description);
    return l_entity;
}

Entity* EntityManager::createPlayerPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Player");
    l_entity->addTag (PLAYER);

    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '@';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity->getId(), l_sprite);


    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity->getId(), l_collider);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "You";
    l_description.text = "Time for introspection";
    getDescriptions()->add (l_entity->getId(), l_description);

    // Health Component
    HealthComponent l_health;
    l_health.health = 1;
    getHealths()->add (l_entity->getId(), l_health);

    return l_entity;
}

Entity* EntityManager::createEnemyPrefab (unsigned int x, unsigned int y)
{
    Entity* l_entity = createEntity("Orc");
    l_entity->addTag (MONSTER);

    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'O';
    l_sprite.xPos       = x;
    l_sprite.yPos       = y;
    getSprites()->add (l_entity->getId(), l_sprite);

    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity->getId(), l_collider);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "Orc";
    l_description.text = "A vile, stinking creature";
    getDescriptions()->add (l_entity->getId(), l_description);

    // Health Component
    HealthComponent l_health;
    l_health.health = 1;
    getHealths()->add (l_entity->getId(), l_health);

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
    getSprites()->add (l_entity->getId(), l_sprite);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "Floor tile";
    l_description.text = "It's a bit scuffed";
    getDescriptions()->add (l_entity->getId(), l_description);

    return l_entity;
}


std::vector<EntityId> EntityManager::findEntitiesAt (unsigned int x, unsigned int y)
{
    return findEntitiesNear (x, y, 0);
}

std::vector<EntityId> EntityManager::findEntitiesNear (unsigned int x, unsigned int y, unsigned radius)
{
    std::vector<EntityId> l_entities;

    std::map<EntityId, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        if (it->second.xPos >= x - radius &&
            it->second.xPos <= x + radius &&
            it->second.yPos >= y - radius &&
            it->second.yPos <= y + radius) {
            l_entities.push_back (it->first);
        }
    }

    return l_entities;

}

std::vector<EntityId> EntityManager::findEntitiesToThe (DIRECTION a_direction, EntityId a_entity)
{
    std::vector<EntityId> l_entities;

    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (a_entity);
    if (!l_sprite) return l_entities;
    unsigned int newX = l_sprite->xPos;
    unsigned int newY = l_sprite->yPos;
    switch (a_direction) {
        case Direction::North:  newY--; break;
        case Direction::South:  newY++; break;
        case Direction::West:   newX--; break;
        case Direction::East:   newX++; break;
        default: return l_entities;
    }

    return findEntitiesAt (newX, newY);
}
