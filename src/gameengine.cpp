#include "gameengine.h"
#include <string>
#include <iostream>
#include <fstream>

GameEngine* GameEngine::s_engine = 0;

GameEngine::GameEngine ()
: m_screen ()
, m_map ()
, m_units ()
, m_isDefender (true)
, m_tick (0)
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
    int ii = 0; 
    int hh = 0; 
    int ww = 0; 
    std::cout << "Loading map: " << mapName << std::endl;
    std::ifstream str (mapName.c_str());
    
    // Load Map
    int mapWidth    = 0; 
    int mapHeight   = 0;
    std::string delim;
    
    str >> mapWidth >> mapHeight >> delim;
    if (mapWidth < 1 || mapHeight < 1) {
        std::cout << "Map too small" << std::endl;
        return;
    }
    std::cout << "Width: " << mapWidth << " Height: " << mapHeight << std::endl;

    m_map.resizeMap (mapHeight, mapWidth); 

    int ground = 0;
    int constr = 0;
    Tile tile;
    for (hh = 1; hh <= mapHeight; hh++) {
        for (ww = 1; ww <= mapHeight; ww++) {
            str >> ground >> constr >> delim;
            tile.setBackground (static_cast<TILE> (ground)); 
            tile.setConstruction (static_cast<CONSTRUCTION>(constr)); 
            tile.setX (ww);
            tile.setY (hh);
            m_map.getTile(ww, hh) = tile;
        }
    }
    std::cout << "Loaded " << hh * ww << " tiles" << std::endl;

    // Now the units
    int defenders = 0;
    int attackers = 0;
    int type = 0;
    int x = 0;
    int y = 0;
    str >> defenders >> attackers >> delim;
    for (ii = 0; ii < defenders + attackers; ii++) {
        str >> type >> x >> y >> delim;
        Unit unit (ii, static_cast<UNIT>(type), x, y);
        unit.isDefender() = (ii < attackers); 
        unit.canSwim() = (ii < attackers); 
        m_units.addUnit (unit);
        m_map.getTile(x, y).setUnit (ii);
    }
    std::cout << "Loaded " << ii << " unit" << std::endl;
}

void GameEngine::start ()
{
    m_screen.initialise();
    m_screen.start();    
}

void GameEngine::tick ()
{
    m_tick++; // Move the engine on
    
    checkVictoryConditions();
    updateFights();
    checkUnitSurroundings();
    updateUnitPath();
}

void GameEngine::checkVictoryConditions ()
{

}

void GameEngine::updateFights()
{
    for (int ii = 0; ii < m_units.getNumUnits(); ii++)
    {
        Unit& l_unit = m_units.getUnit (ii);
        if (l_unit.getTarget() == 0) continue;
           
        if (l_unit.getLastAttack() + 20 < m_tick) {
            Unit& l_enemy = m_units.getUnit(l_unit.getTarget());
            l_enemy.getHitPoints() -= 10; 
            l_unit.setLastAttack (m_tick);
            if (l_enemy.getHitPoints() <= 0) {
                l_unit.getTarget() = 0;
                l_enemy.getTarget() = 0;
                m_units.removeUnit (l_enemy.getId());
            }
        }
    }
}

void GameEngine::checkUnitSurroundings()
{
    int neighbours[4] = {0};
    std::vector<int> l_list;
    m_units.getUnitList (l_list);

    for (int ii = 0; ii < m_units.getNumUnits(); ii++)
    {
        Unit& l_unit = m_units.getUnit (l_list[ii]);
        if (l_unit.getTarget()) continue; // Already attacking someone
        m_map.getNeighbours (   Map::getIndex ( l_unit.getX(), 
                                                l_unit.getY()),
                                neighbours);
        for (int dd = 0; dd < Map::dir; dd++) {
            if (neighbours[dd] == 0) continue;
            int id = m_map.getTile (neighbours[dd]).getUnit();
            if (id) {
                // There is a unit here!
                Unit& l_enemy = m_units.getUnit(id);
                if (l_enemy.isDefender() == l_unit.isDefender() ||
                    l_enemy.getHitPoints() <= 0) { 
                    continue;
                }

                // there's an enemy, let's attack him!
                l_unit.getTarget() = id;
                l_unit.setLastAttack (m_tick);
                if (!l_enemy.getTarget()) {
                    // No enemy yet
                    l_enemy.getTarget() = l_list[ii];
                    l_enemy.setLastAttack (m_tick);
                }
            }
        }
    }
}

void GameEngine::updateUnitPath ()
{
    std::vector<int> l_list;
    m_units.getUnitList (l_list);
    for (int ii = 0; ii < m_units.getNumUnits(); ii++)
    {
        Unit& l_unit = m_units.getUnit (l_list[ii]);
        if (l_unit.getNextTile() >= 0) {
            Tile& currTile = m_map.getTile (l_unit.getX(), l_unit.getY());
            Tile& nextTile = m_map.getTile (l_unit.getNextTile()); 
            int speed = (currTile.getBackground() == TILE_WATER)
                            ? l_unit.getSwimSpeed() 
                            : l_unit.getMoveSpeed();
            if (l_unit.getLastMove() + speed < m_tick) {
                l_unit.moveNextTile (m_tick);
                l_unit.setX (nextTile.getX());
                l_unit.setY (nextTile.getY());
                currTile.setUnit (0);
                nextTile.setUnit (l_unit.getId());
            }
        }
    }
}
