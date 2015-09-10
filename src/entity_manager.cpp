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

EntityId EntityManager::createEntity (Location& location) {
    EntityId l_entity = maxId++;

    location.z = (location.z == 0) ? m_engine->getLevel() : location.z;

    m_locations[l_entity] = location;
    m_engine->getTile (location).entities.insert (l_entity);

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
    getStairs()->remove(id);
    getEquipments()->remove (id);
    getWearables()->remove (id);
    getWieldables()->remove (id);
    getDroppables()->remove (id);

    m_engine->getTile(m_locations[id]).entities.erase (id);

    // Raise event for removal
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}

void EntityManager::setLocation (EntityId entity, Location& location)
{
    m_engine->getTile (m_locations[entity]).entities.erase (entity);
    m_locations[entity] = location;
    m_engine->getTile (m_locations[entity]).entities.insert (entity);
}

EntityId EntityManager::getPlayer () {
    if (m_player == 0) {
        std::map<EntityId, PlayerComponent>& l_players = getPlayers()->getAll();
        std::map<EntityId, PlayerComponent>::iterator iter = l_players.begin();
        m_player = iter->first;
    }
    return m_player;
}


EntityId EntityManager::createWallPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

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

EntityId EntityManager::createPlayerPrefab (Location& location)
{
    EntityId l_entity = createEntity (location);

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
    l_health.health = 10;
    getHealths()->add (l_entity, l_health);

    // Player Component
    PlayerComponent l_player;
    getPlayers()->add (l_entity, l_player);

    // Euipment Component
    EquipmentComponent l_equipment;
    l_equipment.rightHandWieldable = createWeaponPrefab();
    l_equipment.leftHandWieldable = createShieldPrefab();
    l_equipment.headWearable = createHelmetPrefab();
    getEquipments()->add (l_entity, l_equipment);

    return l_entity;
}

EntityId EntityManager::createEnemyPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

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

    // Euipment Component
    EquipmentComponent l_equipment;
    l_equipment.rightHandWieldable = createWeaponPrefab();
    l_equipment.leftHandWieldable = createShieldPrefab();
    l_equipment.headWearable = createHelmetPrefab();
    getEquipments()->add (l_entity, l_equipment);

    return l_entity;
}

EntityId EntityManager::createTilePrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

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

EntityId EntityManager::createMarkerPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

    //Sprite Component
    SpriteComponent l_sprite;
    l_sprite.fgColor    = Color (YELLOW);
    l_sprite.bgColor    = Color (BLACK);
    l_sprite.sprite     = 'X';
    getSprites()->add (l_entity, l_sprite);

    return l_entity;
}

EntityId EntityManager::createStairPrefab (STAIR dir, Location& location)
{
    EntityId l_entity = createEntity(location);

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

EntityId EntityManager::createWeaponPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WieldableComponent l_wieldable;
    l_wieldable.position = WieldableRightHand;
    l_wieldable.baseDamage  = 2;
    l_wieldable.baseDefence = 0;
    getWieldables()->add (l_entity, l_wieldable);

    DescriptionComponent l_description;
    l_description.title = "Sword";
    l_description.text = "Stick 'em with the pointy end!";
    getDescriptions()->add (l_entity, l_description);

    DroppableComponent l_droppable;
    getDroppables()->add (l_entity, l_droppable);
    return l_entity;
}

EntityId EntityManager::createShieldPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WieldableComponent l_wieldable;
    l_wieldable.position = WieldableLeftHand;
    l_wieldable.baseDamage  = 0;
    l_wieldable.baseDefence = 4;
    getWieldables()->add (l_entity, l_wieldable);

    DescriptionComponent l_description;
    l_description.title = "Shield";
    l_description.text = "Return to your mother...";
    getDescriptions()->add (l_entity, l_description);

    DroppableComponent l_droppable;
    getDroppables()->add (l_entity, l_droppable);

    return l_entity;
}

EntityId EntityManager::createHelmetPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WearableComponent l_wearable;
    l_wearable.position = WearableHead;
    getWearables()->add (l_entity, l_wearable);

    DescriptionComponent l_description;
    l_description.title = "Helmet";
    l_description.text = "It says: One Size Fits All";
    getDescriptions()->add (l_entity, l_description);

    DroppableComponent l_droppable;
    getDroppables()->add (l_entity, l_droppable);

    return l_entity;
}

EntityHolder EntityManager::findEntitiesAt (unsigned int x, unsigned int y)
{
    return findEntitiesNear (x, y, 0);
}

EntityHolder EntityManager::findEntitiesNear (unsigned int x, unsigned int y, unsigned radius)
{
    EntityHolder l_entities;

    int startx = x - radius;
    int starty = y - radius;
    int endx = x + radius;
    int endy = y + radius;

    for (int yy = starty; yy <= endy; yy++) {
        for (int xx = startx; xx <= endx; xx++) {
            for (EntityId id : m_engine->getTile (xx, yy, m_engine->getLevel()).entities) {
                l_entities.insert (id);
            }
        }
    }
    return l_entities;

}

EntityHolder EntityManager::findEntitiesToThe (DIRECTION a_direction, EntityId a_entity)
{
    EntityHolder l_entities;

    Location l_location = m_engine->getEntities()->getLocation(a_entity);
    switch (a_direction) {
        case Direction::North:  l_location.y--; break;
        case Direction::South:  l_location.y++; break;
        case Direction::West:   l_location.x--; break;
        case Direction::East:   l_location.x++; break;
        default: return l_entities;
    }
    return findEntitiesAt (l_location.x, l_location.y);
}
