#pragma once

#include "event.h"
#include "game_engine.h"
#include "game_system_interface.h"
#include <memory>
#include <vector>

class GameState;
class EventManager;
class GameSystemBase : public GameSystemInterface {
public:
    virtual ~GameSystemBase() {}

    virtual void initialise(GameEngine* engine);
    virtual void registerHandlers() {}
    virtual void update() {}

protected:
    GameState* state() const { return m_state; }
    std::shared_ptr<EventManager> events() const { return m_events; }
    virtual EntityId instantiatePrefab(const std::string& type,
                                       Location& loc) const;
    virtual GameEngine* getEngine() { return m_engine; }

protected:
    GameEngine* m_engine = nullptr;

private:
    GameState* m_state = nullptr;
    std::shared_ptr<EventManager> m_events = nullptr;
};
