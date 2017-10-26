#include "entity_manager.h"
#include "game_engine.h"
#include "location.h"
#include <fstream>
#include <iostream>
#include <climits>

#include "../components/player_component.h"

void EntityManager::initialise (GameEngineInterface* engine)
{
    m_maxId = 1;
    m_engine = engine;
    m_player = 0;
}

EntityId EntityManager::createEntity (Location& location) {
    EntityId l_entity = m_maxId++;

    if (!location.area) {
        std::cout << "Zero area in createEntity: "
            << l_entity
            << std::endl;
    }

    addEntity (l_entity, location);
    return l_entity;
}

void EntityManager::addEntity (EntityId id, Location& location) {
    if (id >= m_maxId) m_maxId = id + 1;

    m_locations[id] = location;
    m_entities[location.area].insert (id);
    if (validLocation (location)) {
        m_engine->state()->tile(location).addEntity (id);
    }


    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}

void EntityManager::destroyEntity (EntityId id) {
    m_engine->state()->components()->removeAll(id);
    m_engine->state()->tile(m_locations[id]).removeEntity (id);

    m_entities[m_locations[id].area].erase (id);
    m_locations.erase(id);

    // Raise event for removal
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = id;
    m_engine->raiseEvent (l_event);
}

void EntityManager::setLocation (EntityId entity, Location& location)
{
    if (validLocation (m_locations[entity])) {
        m_engine->state()->tile(m_locations[entity]).removeEntity (entity);
        m_entities[location.area].erase (entity);
    }
    m_locations[entity] = location;
    m_engine->state()->map()->setArea (location.area);
    if (validLocation (m_locations[entity])) {
        m_engine->state()->tile(m_locations[entity]).addEntity (entity);
        m_entities[location.area].insert (entity);
    }
}

bool EntityManager::validLocation (Location& location)
{
    return (location.x != UINT_MAX && location.y != UINT_MAX && location.z != UINT_MAX);
}

EntityId EntityManager::getPlayer ()
{
    if (m_player == 0) {
        for (auto map : m_engine->state()->map()->getAreas()) {
            for (EntityId entity : get(map.first)) {
                if (m_engine->state()->components()->get<PlayerComponent>(entity)) {
                    m_player = entity;
                }
            }
        }
    }
    return m_player;
}

EntityHolder& EntityManager::get (unsigned int area)
{
    if (area == 0) {
        area = m_engine->state()->map()->getArea();
    }
    return m_entities[area];
}

