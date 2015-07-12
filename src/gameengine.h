#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "game_engine_interface.h"
#include "graphics_interface.h"
#include "entity_manager_interface.h"
#include "window_manager_interface.h"
#include "game_system_interface.h"
#include "event_manager_interface.h"
#include "generator_interface.h"

#include <string>
#include <cstdlib>

class GameEngine : public GameEngineInterface {
public:
    GameEngine (GraphicsInterface* a_graphics);
    ~GameEngine ();

    void initialise (void);
    void tick (void);

    bool& isPaused() { return m_paused; }
    void quit() { exit (0); }
    void raiseEvent (Event* event) { m_eventManager->raiseEvent (event); }
    EntityManagerInterface* getEntities() { return m_entityManager; }

    void loadMap (const std::string& mapName);

    unsigned long long getTick() { return m_tick; }
    WindowManagerInterface* getWindows() { return m_windowManager; }

    GraphicsInterface* getGraphics() { return m_graphics; }

    void setEntityManager (EntityManagerInterface* a_manager) { m_entityManager = a_manager; }
    void setWindowManager (WindowManagerInterface* a_manager) { m_windowManager = a_manager; }
    void setEventManager (EventManagerInterface* a_manager) { m_eventManager = a_manager; }

    void setSpriteSystem (GameSystemInterface* a_system) { m_spriteSystem = a_system; }
    void setMoveSystem (GameSystemInterface* a_system) { m_moveSystem = a_system; }
    void setGenerator (GeneratorInterface* a_generator) { m_generator = a_generator; }
private:
    unsigned long long  m_tick;
    bool                m_paused;

    EntityManagerInterface* m_entityManager;
    EventManagerInterface*  m_eventManager;
    WindowManagerInterface* m_windowManager;

    GameSystemInterface*    m_moveSystem;
    GameSystemInterface*    m_spriteSystem;

    GraphicsInterface*      m_graphics;
    GeneratorInterface*     m_generator;
};

#endif
