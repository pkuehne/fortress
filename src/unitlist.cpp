#include "unitlist.h"
#include "unit.h"
#include "map.h"

UnitList::UnitList ()
{
    Unit l_unit (UNIT_WARRIOR, 20, 20);
    PathVector l_path;
    
    l_path.push_back (Map::getIndex (19, 20));
    l_path.push_back (Map::getIndex (18, 20));
    l_path.push_back (Map::getIndex (17, 20));
    l_path.push_back (Map::getIndex (16, 20));
    l_path.push_back (Map::getIndex (15, 20));
    l_path.push_back (Map::getIndex (14, 20));
    l_path.push_back (Map::getIndex (13, 20));
    l_unit.setNewPath (l_path);
    m_units.push_back (l_unit);
}
