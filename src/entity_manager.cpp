#include "entity_manager.h"
#include "game_engine.h"
#include <fstream>
#include <iostream>

#include "sprite_component.h"
#include "collider_component.h"
#include "health_component.h"
#include "description_component.h"
#include "player_component.h"
#include "npc_component.h"
#include "stair_component.h"
#include "equipment_component.h"
#include "wearable_component.h"
#include "wieldable_component.h"
#include "droppable_component.h"

void EntityManager::initialise (GameEngineInterface* engine)
{
    m_maxId = 1;
    m_engine = engine;
    m_player = 0;
}

EntityId EntityManager::createEntity (Location& location) {
    EntityId l_entity = m_maxId++;
    addEntity (l_entity, location);
    return l_entity;
}

void EntityManager::addEntity (EntityId id, Location& location) {
    if (id >= m_maxId) m_maxId = id + 1;

    location.z = (location.z == 0) ? m_engine->getLevel() : location.z;
    location.area = (location.area == 0) ? m_engine->getArea() : location.area;

    m_locations[id] = location;
    m_engine->getMap()->getTile (location).entities.insert (id);

    m_entities[location.area].insert (id);

    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}

void EntityManager::destroyEntity (EntityId id) {
    m_engine->getComponents()->removeAll(id);
    m_engine->getMap()->getTile(m_locations[id]).entities.erase (id);

    m_entities[m_engine->getMap()->getArea()].erase (id);

    // Raise event for removal
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}

void EntityManager::setLocation (EntityId entity, Location& location)
{
    m_engine->getMap()->getTile (m_locations[entity]).entities.erase (entity);
    m_locations[entity] = location;
    m_engine->getMap()->setArea (location.area);
    m_engine->getMap()->getTile (m_locations[entity]).entities.insert (entity);
}

EntityId EntityManager::getPlayer ()
{
    if (m_player == 0) {
        for (EntityId entity : m_entities[m_engine->getMap()->getArea()]) {
            if (m_engine->getComponents()->get<PlayerComponent>(entity)) {
                m_player = entity;
            }
        }
    }
    return m_player;
}

EntityHolder& EntityManager::get (unsigned int area)
{
    unsigned int l_area = area;
    if (!l_area) {
        l_area = m_engine->getMap()->getArea();
    }
    return m_entities[l_area];
}

EntityId EntityManager::createWallPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (GREY);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = 'W';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Collider Component
    ColliderComponent* l_collider = new ColliderComponent();
    m_engine->getComponents()->add (l_entity, l_collider);

    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Wall";
    l_description->text = "A smooth granite wall";
    m_engine->getComponents()->add (l_entity, l_description);

    return l_entity;
}

EntityId EntityManager::createPlayerPrefab (Location& location)
{
    EntityId l_entity = createEntity (location);

    // Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (WHITE);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = '@';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Collider Component
    ColliderComponent* l_collider = new ColliderComponent();
    m_engine->getComponents()->add (l_entity, l_collider);

    // Description Component
    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "You";
    l_description->text = "This isn't the time for introspection";
    m_engine->getComponents()->add (l_entity, l_description);

    // Health Component
    HealthComponent* l_health = new HealthComponent();
    l_health->health = 10;
    m_engine->getComponents()->add (l_entity, l_health);

    // Player Component
    PlayerComponent* l_player = new PlayerComponent();
    m_engine->getComponents()->add (l_entity, l_player);

    // Euipment Component
    EquipmentComponent* l_equipment = new EquipmentComponent();
    l_equipment->rightHandWieldable = createWeaponPrefab();
    l_equipment->leftHandWieldable = createShieldPrefab();
    l_equipment->headWearable = createHelmetPrefab();
    m_engine->getComponents()->add (l_entity, l_equipment);

    m_player = l_entity;
    return l_entity;
}

EntityId EntityManager::createEnemyPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (RED);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = 'O';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Collider Component
    ColliderComponent* l_collider = new ColliderComponent();
    m_engine->getComponents()->add (l_entity, l_collider);

    // Description Component
    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Orc";
    l_description->text = "A vile, stinking creature revelling in the dark.";
    m_engine->getComponents()->add (l_entity, l_description);

    // Health Component
    HealthComponent* l_health = new HealthComponent();
    l_health->health = 1;
    m_engine->getComponents()->add (l_entity, l_health);

    // NPC Component
    NpcComponent* l_npc = new NpcComponent();
    m_engine->getComponents()->add (l_entity, l_npc);

    // Euipment Component
    EquipmentComponent* l_equipment = new EquipmentComponent();
    l_equipment->rightHandWieldable = createWeaponPrefab();
    l_equipment->leftHandWieldable = createShieldPrefab();
    l_equipment->headWearable = createHelmetPrefab();
    m_engine->getComponents()->add (l_entity, l_equipment);

    return l_entity;
}

EntityId EntityManager::createTilePrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

    //Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (GREY);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = '.';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Description Component
    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Floor tile";
    l_description->text = "It's a bit scuffed";
    m_engine->getComponents()->add (l_entity, l_description);

    return l_entity;
}

EntityId EntityManager::createMarkerPrefab (Location& location)
{
    EntityId l_entity = createEntity(location);

    //Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (YELLOW);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = 'X';
    m_engine->getComponents()->add (l_entity, l_sprite);

    return l_entity;
}

EntityId EntityManager::createStairPrefab (STAIR dir, Location& location)
{
    EntityId l_entity = createEntity(location);

    //Sprite Component
    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (WHITE);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = (dir == STAIR_DOWN) ? '>' : '<';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Description Component
    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = (dir == STAIR_DOWN) ? "A stairway down" : "A stairway up";
    l_description->text = "It has rough-hewn steps";
    m_engine->getComponents()->add (l_entity, l_description);

    // StairComponent
    StairComponent* l_stair = new StairComponent();
    l_stair->direction = dir;
    l_stair->target = 0;
    m_engine->getComponents()->add (l_entity, l_stair);

    return l_entity;

}

EntityId EntityManager::createWeaponPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WieldableComponent* l_wieldable = new WieldableComponent();
    l_wieldable->position = WieldableRightHand;
    l_wieldable->baseDamage  = 2;
    l_wieldable->baseDefence = 0;
    m_engine->getComponents()->add (l_entity, l_wieldable);

    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Sword";
    l_description->text = "Stick 'em with the pointy end!";
    m_engine->getComponents()->add (l_entity, l_description);

    DroppableComponent* l_droppable = new DroppableComponent();
    m_engine->getComponents()->add (l_entity, l_droppable);

    return l_entity;
}

EntityId EntityManager::createShieldPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WieldableComponent* l_wieldable = new WieldableComponent();
    l_wieldable->position = WieldableLeftHand;
    l_wieldable->baseDamage  = 0;
    l_wieldable->baseDefence = 4;
    m_engine->getComponents()->add (l_entity, l_wieldable);

    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Shield";
    l_description->text = "Return with your shield or upon it!";
    m_engine->getComponents()->add (l_entity, l_description);

    DroppableComponent* l_droppable = new DroppableComponent();
    m_engine->getComponents()->add (l_entity, l_droppable);

    return l_entity;
}

EntityId EntityManager::createHelmetPrefab ()
{
    Location location;
    EntityId l_entity = createEntity(location);

    WearableComponent* l_wearable = new WearableComponent();
    l_wearable->position = WearableHead;
    m_engine->getComponents()->add (l_entity, l_wearable);

    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Helmet";
    l_description->text = "It says: One Size Fits All";
    m_engine->getComponents()->add (l_entity, l_description);

    DroppableComponent* l_droppable = new DroppableComponent();
    m_engine->getComponents()->add (l_entity, l_droppable);

    return l_entity;
}

EntityId EntityManager::createTreePrefab(Location& location)
{
    EntityId l_entity = createEntity (location);

    SpriteComponent* l_sprite = new SpriteComponent();
    l_sprite->fgColor    = Color (DARK_GREEN);
    l_sprite->bgColor    = Color (BLACK);
    l_sprite->sprite     = 'T';
    m_engine->getComponents()->add (l_entity, l_sprite);

    // Description Component
    DescriptionComponent* l_description = new DescriptionComponent();
    l_description->title = "Tree";
    l_description->text = "Or maybe an Ent...?";
    m_engine->getComponents()->add (l_entity, l_description);

    ColliderComponent* l_collider = new ColliderComponent();
    m_engine->getComponents()->add (l_entity, l_collider);

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
            for (EntityId id : m_engine->getMap()->getTile (xx, yy, m_engine->getLevel()).entities) {
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
