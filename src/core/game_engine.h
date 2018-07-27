#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "../core/game_state.h"
#include "../core/window_manager.h"
#include "event_manager_interface.h"
#include "game_system_interface.h"
#include "graphics_interface.h"
#include "location.h"

#include <cstdlib>
#include <string>
#include <vector>

class GameEngine {
public:
    explicit GameEngine(GraphicsInterface* a_graphics);
    ~GameEngine() = default;

    void initialise(void);
    void tick(void);

    void quit() { m_graphics->terminate(); }
    virtual bool isPlayerTurn() { return m_playerTurn; }
    void swapTurn();
    unsigned int getTurn() { return m_turn; }
    void setTurn(unsigned int turn) { m_turn = turn; }

    virtual void raiseEvent(Event* event) { m_eventManager->raiseEvent(event); }

    unsigned long long getTick() { return m_tick; }

    GraphicsInterface* getGraphics() { return m_graphics; }

    void setWindowManager(WindowManager* a_manager) {
        m_windowManager = a_manager;
    }
    void setEventManager(EventManagerInterface* a_manager) {
        m_eventManager = a_manager;
    }
    WindowManager* getWindows() { return m_windowManager; }

    void addSystem(GameSystemInterface* a_system) {
        m_systems.push_back(a_system);
    }

    virtual GameState* state() { return m_state; }

private:
    unsigned long long m_tick = 0;
    bool m_playerTurn = true;
    unsigned int m_turn = 1;

    EventManagerInterface* m_eventManager = nullptr;
    WindowManager* m_windowManager = nullptr;
    GameState* m_state = nullptr;

    std::vector<GameSystemInterface*> m_systems;

    GraphicsInterface* m_graphics = nullptr;

    std::vector<Message> m_messages;
    unsigned int m_depth = 0;
    unsigned int m_area = 0;
};

#endif
