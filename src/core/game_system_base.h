#pragma once

#include "event.h"
#include "game_engine.h"
#include <memory>
#include <vector>

class GameState;
class EventManager;
class GameSystemBase {
public:
    virtual ~GameSystemBase() {}

    virtual void initialise(GameEngine* engine,
                            std::shared_ptr<EventManager> events,
                            std::shared_ptr<ComponentManager> components,
                            std::shared_ptr<EntityManager> entities,
                            std::shared_ptr<MapManager> map);
    virtual void registerHandlers() {}
    virtual void onTick() {}
    virtual void onTurn() {}

protected:
    GameState* state() const { return m_state; }
    std::shared_ptr<ComponentManager> components() const {
        return m_components;
    }
    std::shared_ptr<EntityManager> entities() const { return m_entities; }
    std::shared_ptr<EventManager> events() const { return m_events; }
    std::shared_ptr<MapManager> map() const { return m_map; }
    virtual EntityId instantiatePrefab(const std::string& type,
                                       Location& loc) const;
    virtual GameEngine* getEngine() { return m_engine; }

protected:
    GameEngine* m_engine = nullptr;

private:
    GameState* m_state = nullptr;
    std::shared_ptr<EventManager> m_events = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<MapManager> m_map = nullptr;
};
