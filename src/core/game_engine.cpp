#include "game_engine.h"
#include "../components/player_component.h"
#include "../windows/splash_window.h"
#include "../windows/window.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "game_system_base.h"
#include "map_manager.h"
#include "window_manager.h"
#include <flecs.h>
#include <spdlog/spdlog.h>
#include <string>

struct TurnEvent {};

GameEngine::GameEngine(std::shared_ptr<GraphicsInterface> a_graphics)
    : m_graphics(a_graphics), m_eventManager(std::make_shared<EventManager>()),
      m_windowManager(std::make_unique<WindowManager>()),
      m_map(std::make_shared<MapManager>()),
      m_entities(std::make_shared<EntityManager>()) {
    //
}

void GameEngine::initialise() {

    m_eventManager->subscribe<QuitEvent>(
        [this](auto event) { this->graphics()->terminate(); });

    m_eventManager->subscribe<EndTurnEvent>([this](auto event) {
        auto player = this->entities()->world().lookup("player");
        if (!player.is_valid()) {
            return;
        }
        auto component = player.get_mut<PlayerComponent>();
        component->turn += 1;
        component->playerTurn = !component->playerTurn;

        this->turn();
        entities()->world().lookup("TurnPhase").enable();
    });

    m_eventManager->subscribe<RemoveEntityEvent>([this](auto event) {
        this->entities()->world().delete_with(event.entity);
    });
    m_eventManager->subscribe<UpdateTileSizeEvent>([this](auto event) {
        unsigned int height =
            this->graphics()->getTileHeight() + event.adjustment;
        unsigned int width =
            this->graphics()->getTileWidth() + event.adjustment;
        this->graphics()->updateTileSize(width, height);
        this->events()->fire<ResizeWindowsEvent>();
    });

    // Initialise Managers
    windows()->initialise(graphics(), events(), entities(), map());

    entities()->initialise(events());

    // Initialise Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->initialise(events(), entities(), map());
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

    events()->fire<AddWindowEvent<SplashWindow>>();

    events()->fire<EndTurnEvent>();
}

void GameEngine::tick() {
    m_eventManager->processEvents();

    // Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->onTick();
    }

    entities()->world().progress();

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
