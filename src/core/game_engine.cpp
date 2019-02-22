#include "game_engine.h"
#include "../components/player_component.h"
#include "../windows/splash_window.h"
#include "../windows/window.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "game_system_base.h"
#include "map_manager.h"
#include "window_manager.h"
#include <string>

GameEngine::GameEngine(std::shared_ptr<GraphicsInterface> a_graphics)
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
        [this](auto event) { this->graphics()->terminate(); });

    m_eventManager->subscribe<EndTurnEvent>([&](auto event) {
        auto player = m_state->components()->get<PlayerComponent>(
            m_state->entityManager()->getPlayer());
        if (player) {
            player->turn += 1;
            player->playerTurn = !player->playerTurn;
        }
        this->swapTurn();
    });

    m_eventManager->subscribe<RemoveEntityEvent>([&](auto event) {
        m_state->components()->removeAll(event->entity);
        m_state->entityManager()->destroyEntity(event->entity);
    });
    m_eventManager->subscribe<UpdateTileSizeEvent>([this](auto event) {
        unsigned int height =
            this->graphics()->getTileHeight() + event->adjustment;
        unsigned int width =
            this->graphics()->getTileWidth() + event->adjustment;
        this->graphics()->updateTileSize(width, height);
        this->events()->raise(std::make_shared<ResizeWindowsEvent>());
    });

    // Initialise Managers
    windows()->initialise(graphics(), events(), state()->components(),
                          state()->entityManager(), state()->map());

    // TODO: this needs to be removed
    // and EntityManager no longer
    // dependent on GameEngine
    m_state->entityManager()->initialise(this);

    // Initialise Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->initialise(events(), state()->components(),
                                  state()->entityManager(), state()->map());
    }

    graphics()->setKeyDownFunc([this](unsigned char key, int x, int y) {
        this->windows()->getActive()->keyDown(key);
    });
    graphics()->setKeyUpFunc([this](unsigned char key, int x, int y) {
        this->windows()->getActive()->keyUp(key);
    });
    graphics()->setDisplayFunc([this]() { this->tick(); });
    graphics()->setMouseFunc([this](int button, int state, int x, int y) {
        if (state) {
            this->windows()->getActive()->mouseUp(x, y, button);
        } else {
            this->windows()->getActive()->mouseDown(x, y, button);
        }
    });
    graphics()->setResizeFunc([this](int width, int height) {
        this->graphics()->updateScreenSize(width, height);
        this->windows()->resize();
    });

    events()->raise(std::make_shared<RegisterWindowEvent>(
        std::make_shared<SplashWindow>()));

    events()->raise(std::make_shared<EndTurnEvent>());
}

void GameEngine::tick() {
    m_eventManager->processEvents();

    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTick();
    }

    windows()->nextTick();

    if (!m_playerTurn) {
        swapTurn();
    }
    return;
}

void GameEngine::swapTurn() {
    windows()->nextTurn();

    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTurn();
    }
}
