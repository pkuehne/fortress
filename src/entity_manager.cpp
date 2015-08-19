#include "entity_manager.h"
#include "gameengine.h"
#include <fstream>
#include <iostream>

void EntityManager::initialise (GameEngineInterface* engine)
{
    maxId = 1;
    m_engine = engine;
    m_player = 0;
}

EntityId EntityManager::createEntity () {
    EntityId l_entity = maxId++;

    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = l_entity;
    m_engine->raiseEvent (l_event);

    return l_entity;
}

void EntityManager::destroyEntity (EntityId id) {
    getColliders()->remove (id);
    getSprites()->remove (id);
    getHealths()->remove (id);
    getDescriptions()->remove (id);
    getPlayers()->remove (id);
    getNpcs()->remove (id);
    getLocations()->remove (id);
    getStairs()->remove(id);

    // Raise event for removal
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}


EntityId EntityManager::getPlayer () {
    if (m_player == 0) {
        std::map<EntityId, PlayerComponent>& l_players = getPlayers()->getAll();
        std::map<EntityId, PlayerComponent>::iterator iter = l_players.begin();
        m_player = iter->first;
    }
    return m_player;
}


EntityId EntityManager::createWallPrefab (unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'W';
    getSprites()->add (l_entity, l_sprite);

    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

    DescriptionComponent l_description;
    l_description.title = "Wall";
    l_description.text = "A smooth granite wall";
    getDescriptions()->add (l_entity, l_description);
    return l_entity;
}

EntityId EntityManager::createPlayerPrefab (unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '@';
    getSprites()->add (l_entity, l_sprite);


    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "You";
    l_description.text = "Time for introspection";
    getDescriptions()->add (l_entity, l_description);

    // Health Component
    HealthComponent l_health;
    l_health.health = 1;
    getHealths()->add (l_entity, l_health);

    // Player Component
    PlayerComponent l_player;
    getPlayers()->add (l_entity, l_player);

    return l_entity;
}

EntityId EntityManager::createEnemyPrefab (unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    // Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (RED);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'O';
    getSprites()->add (l_entity, l_sprite);

    // Collider Component
    ColliderComponent l_collider;
    getColliders()->add (l_entity, l_collider);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "Orc";
    l_description.text = "A vile, stinking creature";
    getDescriptions()->add (l_entity, l_description);

    // Health Component
    HealthComponent l_health;
    l_health.health = 1;
    getHealths()->add (l_entity, l_health);

    // NPC Component
    NpcComponent l_npc;
    getNpcs()->add (l_entity, l_npc);

    return l_entity;
}

EntityId EntityManager::createTilePrefab (unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (GREY);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = '.';
    getSprites()->add (l_entity, l_sprite);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = "Floor tile";
    l_description.text = "It's a bit scuffed";
    getDescriptions()->add (l_entity, l_description);

    return l_entity;
}

EntityId EntityManager::createMarkerPrefab (unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (YELLOW);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'X';
    getSprites()->add (l_entity, l_sprite);

    return l_entity;
}

EntityId EntityManager::createStairPrefab (STAIR dir, unsigned int x, unsigned int y, unsigned int z)
{
    EntityId l_entity = createEntity();

    // Location Component
    LocationComponent l_loc;
    l_loc.x = x;
    l_loc.y = y;
    l_loc.z = (z == 0)  ? m_engine->getLevel() : z;
    getLocations()->add (l_entity, l_loc);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (WHITE);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = (dir == STAIR_DOWN) ? '>' : '<';
    getSprites()->add (l_entity, l_sprite);

    // Description Component
    DescriptionComponent l_description;
    l_description.title = (dir == STAIR_DOWN) ? "A stairway down" : "A stairway up";
    l_description.text = "It has rough-hewn steps.";
    getDescriptions()->add (l_entity, l_description);

    // StairComponent
    StairComponent l_stair;
    l_stair.direction = dir;
    getStairs()->add (l_entity, l_stair);

    return l_entity;

}

std::vector<EntityId> EntityManager::findEntitiesAt (unsigned int x, unsigned int y)
{
    return findEntitiesNear (x, y, 0);
}

std::vector<EntityId> EntityManager::findEntitiesNear (unsigned int x, unsigned int y, unsigned radius)
{
    std::vector<EntityId> l_entities;

    std::map<EntityId, LocationComponent>& l_locations = m_engine->getEntities()->getLocations()->getAll();
    std::map<EntityId, LocationComponent>::iterator it = l_locations.begin();
    for (; it != l_locations.end(); it++) {
        if (it->second.x >= x - radius &&
            it->second.x <= x + radius &&
            it->second.y >= y - radius &&
            it->second.y <= y + radius &&
            it->second.z == m_engine->getLevel()) {
            l_entities.push_back (it->first);
        }
    }

    return l_entities;

}

std::vector<EntityId> EntityManager::findEntitiesToThe (DIRECTION a_direction, EntityId a_entity)
{
    std::vector<EntityId> l_entities;

    LocationComponent* l_location = m_engine->getEntities()->getLocations()->get (a_entity);
    if (!l_location) return l_entities;
    unsigned int newX = l_location->x;
    unsigned int newY = l_location->y;
    switch (a_direction) {
        case Direction::North:  newY--; break;
        case Direction::South:  newY++; break;
        case Direction::West:   newX--; break;
        case Direction::East:   newX++; break;
        default: return l_entities;
    }

    return findEntitiesAt (newX, newY);
}
