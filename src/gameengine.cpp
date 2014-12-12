#include "gameengine.h"
#include <string>
#include <iostream>

GameEngine* GameEngine::s_engine = 0;

GameEngine::GameEngine ()
: m_screen ()
, m_map ()
, m_units ()
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
    m_screen.initialise();
    m_screen.start();    
}

void GameEngine::tick ()
{
    //std::cout << "Ticking..." << std::endl;
    
    updateUnitPath();
}

void GameEngine::updateUnitPath ()
{
    UnitVector::iterator iter = m_units.getUnits().begin();
    for (; iter != m_units.getUnits().end(); iter++)
    {
        int tile = iter->getNextPath(); 
        if (tile) {
           Tile l_tile = m_map.getTile (tile); 
           iter->setX (l_tile.getX());
           iter->setY (l_tile.getY());
        }
    }
}
