#include "game_system_base.h"

void GameSystemBase::initialise(GameEngine* engine,
                                std::shared_ptr<EventManager> events,
                                std::shared_ptr<ComponentManager> components,
                                std::shared_ptr<EntityManager> entities,
                                std::shared_ptr<MapManager> map) {
    m_engine = engine;
    m_events = events;
    m_components = components;
    m_entities = entities;
    m_map = map;
    registerHandlers();
}

EntityId GameSystemBase::instantiatePrefab(const std::string& type,
                                           Location& location) const {
    if (type.empty()) {
        return 0;
    }

    EntityId entity = entities()->createEntity(location);
    events()->raise(std::make_shared<InstantiatePrefabEvent>(entity, type));
    return entity;
}