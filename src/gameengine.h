#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "graphics.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "window_manager.h"

#include "movement_system.h"
#include "sprite_system.h"

#include <string>

class GameEngine {
public:
    static GameEngine* getEngine ();

    void initialise (void);
    void tick (void);
    void start (void) { start_graphics(); }

    bool& isPaused() { return m_paused; }

    void raiseEvent (Event* event) { m_eventManager.raiseEvent (event); }
    EntityManager& getEntities() { return m_entityManager; }

    void loadMap (const std::string& mapName);

    unsigned long long getTick() { return m_tick; }
    WindowManager& getWindows() { return m_windowManager; }
    Window* getCurrentWindow() { return m_windowManager.getWindow(); }

private:
    GameEngine ();
    ~GameEngine ();
    static GameEngine*  s_engine;

private:
    unsigned long long  m_tick;
    bool                m_paused;

    EntityManager       m_entityManager;
    EventManager        m_eventManager;
    WindowManager       m_windowManager;

    MovementSystem      m_moveSystem;
    SpriteSystem        m_spriteSystem;
};

#endif
