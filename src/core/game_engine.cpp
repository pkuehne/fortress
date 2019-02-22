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
    : m_graphics(a_graphics), m_eventManager(std::make_shared<EventManager>()),
      m_windowManager(std::make_unique<WindowManager>()),
      m_map(std::make_shared<MapManager>()),
      m_entities(std::make_shared<EntityManager>()),
      m_components(std::make_shared<ComponentManager>()) {
    //
}

void GameEngine::initialise() {
    m_eventManager->subscribe<QuitEvent>(
        [this](auto event) { this->graphics()->terminate(); });

    m_eventManager->subscribe<EndTurnEvent>([this](auto event) {
        auto player = this->components()->get<PlayerComponent>(
            this->entities()->getPlayer());
        if (player) {
            player->turn += 1;
            player->playerTurn = !player->playerTurn;
        }
        this->turn();
    });

    m_eventManager->subscribe<RemoveEntityEvent>([this](auto event) {
        this->components()->removeAll(event->entity);
        this->entities()->destroyEntity(event->entity);
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
    windows()->initialise(graphics(), events(), components(), entities(),
                          map());

    entities()->initialise(events(), map(), components());

    // Initialise Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->initialise(events(), components(), entities(), map());
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
    return;
}

void GameEngine::turn() {
    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTurn();
    }
    windows()->nextTurn();
}
