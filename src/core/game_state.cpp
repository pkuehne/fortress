#include "game_state.h"
#include "entity_manager.h"
#include "map_manager.h"
#include <glog/logging.h>
#include <stdexcept>

GameState::GameState(MapManager* map, EntityManager* entities,
                     ComponentManager* components)
    : m_map(map), m_entities(entities), m_components(components),
      m_prefabs(entities, components) {
    if (m_map == nullptr || m_entities == nullptr || m_components == nullptr) {
        LOG(ERROR) << "Game State initialised with nullptr" << std::endl;
        throw std::logic_error("Input parameter cannot be nullptr");
    }
}

Tile& GameState::tile(const Location& location) {
    return m_map->getTile(location);
}

bool GameState::isValidTile(const Location& location) {
    return m_map->isValidTile(location);
}

Location GameState::location(const Location& location, Direction direction) {
    return m_map->location(location, direction);
}

MapManager* GameState::map() { return m_map; }

EntityManager* GameState::entityManager() { return m_entities; }

ComponentManager* GameState::components() { return m_components; }

const EntityHolder& GameState::entities() { return m_entities->get(); }

EntityHolder GameState::entities(const Location& loc) {
    return m_map->findEntitiesAt(loc);
}

EntityId GameState::player() { return m_entities->getPlayer(); }

EntityId GameState::createEntity(Location& location) {
    return m_entities->createEntity(location);
}

Location GameState::location(EntityId entity) {
    return m_entities->getLocation(entity);
}

void GameState::setArea(unsigned int area) { m_map->setArea(area); }

unsigned int GameState::getArea() { return m_map->getArea(); }

// void save(const std::string& filename) {
//     // TODO: YAML savefile
// }

// void load(const std::string& filename) {
//     // TODO: YAML savefile
// }

void GameState::addMessage(const Message& message) {
    m_messages.push_back(message);
}

void GameState::addMessage(const MessageType& severity,
                           const std::string& message) {
    Message msg;
    msg.severity = severity;
    msg.message = message;
    addMessage(msg);
}

std::vector<Message>& GameState::getMessages() { return m_messages; }
