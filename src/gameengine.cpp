#include "gameengine.h"
#include <string>
// #include <iostream>
// #include <fstream>
// #include <cmath>

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
    m_windowManager.initialise();
    m_entityManager.initialise();
    m_eventManager.initialise();

    m_eventManager.registerHandler (m_moveSystem);

    loadMap ("");
    setup_graphics();
}

void GameEngine::loadMap (const std::string& mapName)
{
    m_entityManager.createPlayerEntity (10, 10);
    m_entityManager.createEnemyEntity (12, 12);

    m_entityManager.createWallEntity ( 9,  9);
    m_entityManager.createWallEntity ( 9, 10);
    m_entityManager.createWallEntity ( 9, 11);
    m_entityManager.createWallEntity ( 9, 12);
    m_entityManager.createWallEntity (10,  9);
    m_entityManager.createWallEntity (11,  9);
    m_entityManager.createWallEntity (12,  9);

    m_entityManager.createRoom (17, 19, 25, 35);
}

void GameEngine::tick ()
{
    if (m_paused) return;

    m_tick++; // Move the engine on

    m_eventManager.processEvents();

    //Update Systems

    return;
}
