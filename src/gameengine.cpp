#include "gameengine.h"
#include <string>

#include "generator.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "window_manager.h"
#include "movement_system.h"
#include "combat_system.h"
#include "sprite_system.h"

GameEngine* g_engine = 0;

static void keyDown (unsigned char key, int x, int y)
{
    g_engine->getWindows()->getActive()->keyDown (key);
}

static void keyUp (unsigned char key, int x, int y)
{
    g_engine->getWindows()->getActive()->keyUp (key);
}

static void display (void)
{
    g_engine->tick();
}

static void mouseClick (int button, int state, int x, int y)
{
    if (state) {
        g_engine->getWindows()->getActive()->mouseUp (x, y, button);
    } else {
        g_engine->getWindows()->getActive()->mouseDown (x, y, button);
    }
}

GameEngine::GameEngine (GraphicsInterface* a_graphics)
: m_tick (0)
, m_paused (false)
, m_entityManager (0)
, m_eventManager (0)
, m_windowManager (0)
, m_moveSystem (0)
, m_spriteSystem (0)
, m_combatSystem (0)
, m_graphics (a_graphics)
, m_generator (0)
{
    g_engine = this;
}

GameEngine::~GameEngine ()
{

}

void GameEngine::initialise ()
{
    // Create if not exist
    if (!m_windowManager) m_windowManager = new WindowManager();
    if (!m_eventManager)  m_eventManager  = new EventManager();
    if (!m_entityManager) m_entityManager = new EntityManager();
    if (!m_moveSystem)    m_moveSystem    = new MovementSystem();
    if (!m_spriteSystem)  m_spriteSystem  = new SpriteSystem();
    if (!m_generator)     m_generator     = new Generator();
    if (!m_combatSystem)  m_combatSystem  = new CombatSystem();

    // Initialise Managers
    m_windowManager->initialise (this);
    m_entityManager->initialise (this);
    m_eventManager->initialise  (this);

    // Initialise Systems
    m_moveSystem->initialise (this);
    m_spriteSystem->initialise (this);
    m_combatSystem->initialise (this);

    // Initialise Map Generator
    m_generator->initialise (this);

    // Register Systems with Event Manager
    m_eventManager->registerHandler (m_moveSystem);
    m_eventManager->registerHandler (m_spriteSystem);
    m_eventManager->registerHandler (m_combatSystem);

    m_graphics->setKeyboardFunc (keyDown);
    m_graphics->setKeyboardUpFunc (keyUp);
    m_graphics->setDisplayFunc  (display);
    m_graphics->setMouseFunc    (mouseClick);

}

void GameEngine::loadMap (const std::string& mapName)
{
    m_generator->mapHeight() = 50;
    m_generator->mapWidth() = 50;
    m_generator->numberOfRooms() = 1;

    m_generator->generate();
}

void GameEngine::tick ()
{
    if (!m_paused) {
        m_tick++; // Move the engine on

        m_eventManager->processEvents();

        //Update Systems
        m_moveSystem->update();
        m_spriteSystem->update();
        m_combatSystem->update();
    }
    getWindows()->getActive()->beforeRedraw();
    getWindows()->getActive()->redraw();
    getWindows()->getActive()->afterRedraw();

    return;
}
