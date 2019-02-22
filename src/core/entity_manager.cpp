#include "entity_manager.h"
#include "event_manager.h"
#include "location.h"
#include <climits>
#include <fstream>
#include <iostream>

#include "../components/player_component.h"

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

    m_events->raise(std::make_shared<AddEntityEvent>(id, location));
}

void EntityManager::destroyEntity(EntityId id) {
    Location& location = m_locations[id];

    if (location.isValid()) {
        m_entities[m_locations[id].area].erase(id);
    }
    m_locations.erase(id);
    m_allEntities.erase(id);
}

void EntityManager::setLocation(EntityId entity, const Location& location) {
    if (!entity) {
        return;
    }
    if (m_locations[entity].isValid()) {
        m_entities[location.area].erase(entity);
    }
    Location prev = m_locations[entity];
    m_locations[entity] = location;
    if (m_locations[entity].isValid()) {
        m_entities[location.area].insert(entity);
    }
    m_events->raise(
        std::make_shared<ChangeLocationEvent>(entity, prev, location));
}

EntityId EntityManager::getPlayer() {
    if (m_player == 0) {
        for (auto map : m_map->getAreas()) {
            for (EntityId entity : get(map.first)) {
                if (m_components->get<PlayerComponent>(entity)) {
                    m_player = entity;
                }
            }
        }
    }
    return m_player;
}
