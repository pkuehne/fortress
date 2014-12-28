#include "unit.h"
#include "map.h"
#include "algorithm.h"
#include <iostream>

Unit::Unit ()
: m_id (0)
, m_type (UNIT_WARRIOR)
, m_x (1)
, m_y (1)
, m_canSwim (false)
, m_lastMove (0)
, m_moveSpeed (10)
, m_swimSpeed (30) 
, m_hitPoints (100)
, m_target (0)
, m_lastAttack (0)
{
}

Unit::Unit (int id, UNIT type, int x, int y)
: m_id (id)
, m_type (type)
, m_x (x)
, m_y (y)
, m_canSwim (false)
, m_lastMove (0)
, m_moveSpeed (10)
, m_swimSpeed (30)
, m_hitPoints (100)
, m_target (0)
, m_lastAttack (0)
{

}

void Unit::setNewDestination (int x , int y)
{
    PathVector l_path;
    Algorithm::findUnitPath (   Map::getIndex (m_x, m_y), 
                                Map::getIndex (x, y), 
                                *this,
                                l_path);
    setNewPath (l_path);
}

int Unit::getNextTile() 
{
    int retval = -1;
    if (m_path.size() > 0) {
        retval = m_path.back();
    }
    return retval;
}

// \todo MoveNextTile needs to be handled better - this doesn't actually do any moving
void Unit::moveNextTile (unsigned long long tick)
{
    if (m_path.size() > 0) {
        m_path.pop_back();
    }
    m_lastMove = tick;
}
