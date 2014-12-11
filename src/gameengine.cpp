#include "gameengine.h"
#include <string>

GameEngine* GameEngine::s_engine = 0;

GameEngine::GameEngine ()
: m_screen ()
, m_map()
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

void GameEngine::generateMap (int seed /* = 0 */)
{
    //Generator l_generator (m_map);
    //if (seed) l_generator.setSeed (seed);
    //l_generator.generate();
}
    
void GameEngine::loadMap (const std::string& mapName)
{

}

void GameEngine::execute ()
{
    m_screen.init();    
}
