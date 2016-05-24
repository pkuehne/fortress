#include "game_engine.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "window_manager.h"
#include "map_manager.h"
#include "fov_algorithm.h"
#include <string>

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

static void resize (int width, int height)
{
    g_engine->getGraphics()->updateScreenSize (width, height);
    g_engine->getWindows()->resize();
}

GameEngine::GameEngine (GraphicsInterface* a_graphics)
: m_tick (0)
, m_playerTurn (true)
, m_turn (1)
, m_entityManager (0)
, m_eventManager (0)
, m_windowManager (0)
, m_componentManager (0)
, m_mapManager (0)
, m_graphics (a_graphics)
{
    g_engine = this;
}

GameEngine::~GameEngine ()
{

}

void GameEngine::initialise ()
{
    // Start us off on level 1
    m_depth = 1;

    // Create if not exist
    if (!m_windowManager)       m_windowManager     = new WindowManager();
    if (!m_eventManager)        m_eventManager      = new EventManager();
    if (!m_entityManager)       m_entityManager     = new EntityManager();
    if (!m_componentManager)    m_componentManager  = new ComponentManager();
    if (!m_mapManager)          m_mapManager        = new MapManager();

    // Initialise Managers
    m_windowManager->initialise     (this);
    m_eventManager->initialise      (this);
    m_entityManager->initialise     (this);

    // Initialise Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->initialise (this);
        m_eventManager->registerHandler (m_systems[ii]);
    }

    m_graphics->setKeyDownFunc  (keyDown);
    m_graphics->setKeyUpFunc    (keyUp);
    m_graphics->setDisplayFunc  (display);
    m_graphics->setMouseFunc    (mouseClick);
    m_graphics->setResizeFunc   (resize);

    addMessage (INFO, "You find yourself in a forest.");
    addMessage (INFO, "Stairs will lead you into the dungeons.");
    addMessage (WARN, "Beware the Troll living in the depths!");

    swapTurn();
}

void GameEngine::tick ()
{
    m_tick++; // Move the engine on

    m_eventManager->processEvents();

    //Update Systems
    for (unsigned int ii = 0; ii < m_systems.size(); ii++) {
        m_systems[ii]->update();
    }

    getWindows()->update();
    getWindows()->redraw();

    if (!m_playerTurn) swapTurn();
    return;
}

void GameEngine::addMessage (const MessageType& severity, const std::string& message)
{
    Message msg;
    msg.severity = severity;
    msg.message = message;
    addMessage (msg);
}

void GameEngine::swapTurn()
{
    m_playerTurn = !m_playerTurn;
    m_turn++;

    FovAlgorithm l_algo;
    l_algo.initialise (this);
    l_algo.calculateFov();
}

