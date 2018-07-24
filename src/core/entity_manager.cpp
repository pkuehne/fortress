#include "entity_manager.h"
#include "game_engine.h"
#include "location.h"
#include <climits>
#include <fstream>
#include <iostream>

#include "../components/player_component.h"

void EntityManager::initialise(GameEngine* engine) {
    m_maxId = 1;
    m_engine = engine;
    m_player = 0;
}

EntityId EntityManager::createEntity(const Location& location) {
    EntityId l_entity = m_maxId++;

    addEntity(l_entity, location);
    return l_entity;
}

void EntityManager::addEntity(EntityId id, const Location& location) {
    if (id >= m_maxId)
        m_maxId = id + 1;

    m_locations[id] = location;
    m_entities[location.area].insert(id);
    m_allEntities.insert(id);
    if (location.isValid()) {
        m_engine->state()->tile(location).addEntity(id);
    }

    AddEntityEvent* l_event = new AddEntityEvent;
    l_event->entity = id;
    m_engine->raiseEvent(l_event);
}

void EntityManager::destroyEntity(EntityId id) {
    Location& location = m_locations[id];

    m_engine->state()->components()->removeAll(id);
    if (location.isValid()) {
        m_engine->state()->tile(m_locations[id]).removeEntity(id);
        m_entities[m_locations[id].area].erase(id);
    }
    m_locations.erase(id);
    m_allEntities.erase(id);

    // Raise event for removal
    RemoveEntityEvent* l_event = new RemoveEntityEvent();
    l_event->entity = id;
    m_engine->raiseEvent(l_event);
}

void EntityManager::setLocation(EntityId entity, const Location& location) {
    if (!entity) {
        return;
    }
    if (m_locations[entity].isValid()) {
        m_engine->state()->tile(m_locations[entity]).removeEntity(entity);
        m_entities[location.area].erase(entity);
    }
    m_locations[entity] = location;
    if (m_locations[entity].isValid()) {
        m_engine->state()->tile(m_locations[entity]).addEntity(entity);
        m_entities[location.area].insert(entity);
    }
}

EntityId EntityManager::getPlayer() {
    if (m_player == 0) {
        for (auto map : m_engine->state()->map()->getAreas()) {
            for (EntityId entity : get(map.first)) {
                if (m_engine->state()->components()->get<PlayerComponent>(
                        entity)) {
                    m_player = entity;
                }
            }
        }
    }
    return m_player;
}
