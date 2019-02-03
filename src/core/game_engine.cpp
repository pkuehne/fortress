#include "game_engine.h"
#include "../algos/fov_algorithm.h"
#include "../windows/splash_window.h"
#include "../windows/window.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "game_system_base.h"
#include "map_manager.h"
#include "window_manager.h"
#include <string>

GameEngine::GameEngine(GraphicsInterface* a_graphics)
    : m_graphics(a_graphics), m_eventManager(std::make_shared<EventManager>()) {
}

void GameEngine::initialise() {
    // Create if not exist
    if (!m_windowManager) {
        m_windowManager = new WindowManager();
    }
    if (!m_state) {
        m_state = new GameState();
    }

    m_eventManager->subscribe<QuitEvent>(
        [&](auto event) { m_graphics->terminate(); });

    // Initialise Managers
    m_windowManager->initialise(this);

    // TODO: this needs to be removed
    // and EntityManager no longer
    // dependent on GameEngine or
    // GameState
    m_state->entityManager()->initialise(this);

    // Initialise Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->initialise(this, m_eventManager, state()->components(),
                                  state()->entityManager(), state()->map());
    }

    m_graphics->setKeyDownFunc([&](unsigned char key, int x, int y) {
        getWindows()->getActive()->keyDown(key);
    });
    m_graphics->setKeyUpFunc([&](unsigned char key, int x, int y) {
        getWindows()->getActive()->keyUp(key);
    });
    m_graphics->setDisplayFunc([&]() { tick(); });
    m_graphics->setMouseFunc([&](int button, int state, int x, int y) {
        if (state) {
            getWindows()->getActive()->mouseUp(x, y, button);
        } else {
            getWindows()->getActive()->mouseDown(x, y, button);
        }
    });
    m_graphics->setResizeFunc([&](int width, int height) {
        getGraphics()->updateScreenSize(width, height);
        getWindows()->resize();
    });

    m_eventManager->raise(std::make_shared<RegisterWindowEvent>(
        std::make_shared<SplashWindow>()));

    swapTurn();
}

void GameEngine::tick() {
    m_tick++; // Move the engine on

    m_eventManager->processEvents();

    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTick();
    }

    getWindows()->nextTick();

    if (!m_playerTurn) {
        swapTurn();
    }
    return;
}

void GameEngine::swapTurn() {
    m_playerTurn = !m_playerTurn;
    m_turn++;

    m_state->nextTurn();
    getWindows()->nextTurn();

    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTurn();
    }

    FovAlgorithm l_algo;
    l_algo.initialise(this);
    l_algo.calculateFov();
}
