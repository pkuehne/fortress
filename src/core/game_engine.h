#pragma once

#include "../core/game_state.h"
#include "../core/window_manager.h"
#include "event_manager.h"
#include "graphics_interface.h"
#include "location.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

// class EventManager;
class GameSystemBase;

class GameEngine {
public:
    explicit GameEngine(std::shared_ptr<GraphicsInterface> a_graphics);
    ~GameEngine() = default;

    void initialise(void);
    void tick(void);

    std::shared_ptr<GraphicsInterface> graphics() { return m_graphics; }
    virtual std::shared_ptr<EventManager> events() { return m_eventManager; }
    virtual std::unique_ptr<WindowManager>& windows() {
        return m_windowManager;
    }

    void addSystem(GameSystemBase* a_system) { m_systems.push_back(a_system); }

    virtual GameState* state() { return m_state; }

private:
    void swapTurn();

private:
    std::shared_ptr<GraphicsInterface> m_graphics = nullptr;
    std::shared_ptr<EventManager> m_eventManager = nullptr;
    std::unique_ptr<WindowManager> m_windowManager = nullptr;

    unsigned long long m_tick = 0;
    bool m_playerTurn = true;
    unsigned int m_turn = 1;

    GameState* m_state = nullptr;

    std::vector<GameSystemBase*> m_systems;
};
