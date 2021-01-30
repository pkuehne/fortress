#include "game_system_base.h"
#include "event.h"

void GameSystemBase::initialise(std::shared_ptr<EventManager> events,
                                std::shared_ptr<ComponentManager> components,
                                std::shared_ptr<EntityManager> entities,
                                std::shared_ptr<MapManager> map) {
    m_events = events;
    m_components = components;
    m_entities = entities;
    m_map = map;
    registerHandlers();
}

EntityId GameSystemBase::instantiatePrefab(const std::string& type,
                                           const Location& location) const {
    if (type.empty()) {
        return 0;
    }

    EntityId entity = entities()->createEntity(location);
    events()->fire(std::make_shared<InstantiatePrefabEvent>(entity, type));
    return entity;
}