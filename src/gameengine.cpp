#include "gameengine.h"
//#include "generator.h"

GameEngine* GameEngine::s_engine = 0;

GameEngine::GameEngine ()
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
