#include "gameengine.h"
#include "generator.h"
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

GameEngine::GameEngine (GraphicsInterface* a_graphics)
: m_tick (0)
, m_paused (false)
, m_windowManager (0)
, m_graphics (a_graphics)
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

    // Initialise Managers
    m_windowManager->initialise (this);
    m_entityManager.initialise (this);
    m_eventManager.initialise  (this);

    // Initialise Systems
    m_moveSystem.initialise (this);
    m_spriteSystem.initialise (this);

    // Register Systems with Event Manager
    m_eventManager.registerHandler (&m_moveSystem);
    m_eventManager.registerHandler (&m_spriteSystem);

    m_graphics->setKeyboardFunc (keyDown);
    m_graphics->setKeyboardUpFunc (keyUp);
    m_graphics->setDisplayFunc  (display);
    m_graphics->setMouseFunc    (mouseClick);
}

void GameEngine::loadMap (const std::string& mapName)
{

    GEN_PARAMS params;
    params.height   = 50;
    params.width    = 50;
    params.rooms    = 1;
    generateDungeon (this, params);

}

void GameEngine::tick ()
{
    if (!m_paused) {
        m_tick++; // Move the engine on

        m_eventManager.processEvents();

        //Update Systems
        m_moveSystem.update();
        m_spriteSystem.update();
        }
    getWindows()->getActive()->beforeRedraw();
    getWindows()->getActive()->redraw();
    getWindows()->getActive()->afterRedraw();

    return;
}
