#pragma once

#include "../core/component_manager.h"
#include "../core/entity.h"
#include "../core/entity_manager.h"
#include "../core/event.h"
#include "../core/event_manager.h"
#include "../core/map_manager.h"
#include "entity.h"
#include "location.h"
#include <memory>
#include <vector>

class GameSystemBase {
public:
    virtual ~GameSystemBase() {}

    virtual void initialise(std::shared_ptr<EventManager> events,
                            std::shared_ptr<ComponentManager> components,
                            std::shared_ptr<EntityManager> entities,
                            std::shared_ptr<MapManager> map);
    virtual void registerHandlers() {}
    virtual void onTick() {}
    virtual void onTurn() {}

protected:
    std::shared_ptr<ComponentManager> components() const {
        return m_components;
    }
    std::shared_ptr<EntityManager> entities() const { return m_entities; }
    std::shared_ptr<EventManager> events() const { return m_events; }
    std::shared_ptr<MapManager> map() const { return m_map; }
    virtual EntityId instantiatePrefab(const std::string& type,
                                       const Location& loc) const;

private:
    std::shared_ptr<EventManager> m_events = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<MapManager> m_map = nullptr;
};
