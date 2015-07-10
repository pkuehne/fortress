#include "gameengine.h"
#include "generator.h"
#include <string>

GameEngine* GameEngine::s_engine = 0;

GameEngine::GameEngine ()
: m_tick (0)
, m_paused (false)
{

}

GameEngine::~GameEngine ()
{
    if (s_engine) delete s_engine;
}

GameEngine* GameEngine::getEngine ()
{
    if (!s_engine) s_engine = new GameEngine;
    return s_engine;
}

void GameEngine::initialise ()
{
    // Initialise Managers
    m_windowManager.initialise (this);
    m_entityManager.initialise (this);
    m_eventManager.initialise  (this);

    // Initialise Systems
    m_moveSystem.initialise (this);
    m_spriteSystem.initialise (this);

    // Register Systems with Event Manager
    m_eventManager.registerHandler (&m_moveSystem);
    m_eventManager.registerHandler (&m_spriteSystem);

    setup_graphics();
}

void GameEngine::loadMap (const std::string& mapName)
{

    GEN_PARAMS params;
    params.height   = 50;
    params.width    = 50;
    params.rooms    = 1;
    generateDungeon (params);

}

void GameEngine::tick ()
{
    if (m_paused) return;

    m_tick++; // Move the engine on

    m_eventManager.processEvents();

    //Update Systems
    m_moveSystem.update();
    m_spriteSystem.update();

    return;
}
