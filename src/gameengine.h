#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "game_engine_interface.h"
#include "graphics_interface.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "window_manager.h"

#include "movement_system.h"
#include "sprite_system.h"

#include <string>

class GameEngine : public GameEngineInterface {
public:
    GameEngine (GraphicsInterface* a_graphics);
    ~GameEngine ();

    void initialise (void);
    void tick (void);

    bool& isPaused() { return m_paused; }

    void raiseEvent (Event* event) { m_eventManager.raiseEvent (event); }
    EntityManagerInterface* getEntities() { return m_entityManager; }

    void loadMap (const std::string& mapName);

    unsigned long long getTick() { return m_tick; }
    WindowManagerInterface* getWindows() { return m_windowManager; }

    GraphicsInterface* getGraphics() { return m_graphics; }

private:
    unsigned long long  m_tick;
    bool                m_paused;

    EntityManagerInterface* m_entityManager;
    EventManager            m_eventManager;
    WindowManagerInterface* m_windowManager;

    MovementSystem          m_moveSystem;
    SpriteSystem            m_spriteSystem;

    GraphicsInterface*      m_graphics;
};

#endif
