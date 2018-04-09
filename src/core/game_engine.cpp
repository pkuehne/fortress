#include "game_engine.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "window_manager.h"
#include "../windows/window.h"
#include "map_manager.h"
#include "../algos/fov_algorithm.h"
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
, m_eventManager (0)
, m_windowManager (0)
, m_state (0)
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
    if (!m_state)               m_state             = new GameState();

    // Initialise Managers
    m_windowManager->initialise (this);

    //TODO: this needs to be removed
    // and EntityManager no longer
    // dependent on GameEngine or
    // GameState
    m_state->entityManager()->initialise (this);

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

    m_state->addMessage (INFO, "You find yourself in a forest.");
    m_state->addMessage (INFO, "Stairs will lead you into the dungeons.");
    m_state->addMessage (WARN, "Beware the Troll living in the depths!");

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

    getWindows()->nextTick();

    if (!m_playerTurn) swapTurn();
    return;
}

void GameEngine::swapTurn()
{
    m_playerTurn = !m_playerTurn;
    m_turn++;

    m_state->nextTurn();
    getWindows()->nextTurn();


    FovAlgorithm l_algo;
    l_algo.initialise (this);
    l_algo.calculateFov();
}

