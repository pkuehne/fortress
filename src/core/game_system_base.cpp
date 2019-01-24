#include "game_system_base.h"

void GameSystemBase::initialise(GameEngine* engine) {
    m_engine = engine;
    m_state = engine->state();
    m_events = engine->events();
    registerHandlers();
}

EntityId GameSystemBase::instantiatePrefab(const std::string& type,
                                           Location& location) const {
    if (type.empty()) {
        return 0;
    }

    EntityId entity = state()->createEntity(location);
    events()->raise(std::make_shared<InstantiatePrefabEvent>(entity, type));
    return entity;
}