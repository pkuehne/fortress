#ifndef __UNITLIST_H__
#define __UNITLIST_H__

#include "unit.h"
#include <map>

typedef std::map<int, Unit> UnitMap;
typedef UnitMap::iterator   UnitIter;

class UnitList {
public:
    UnitList ();

    Unit& getUnit (int id);
    void addUnit (Unit& unit) { m_units[unit.getId()] = unit; }
    void removeUnit (int id);
    
    int getNumUnits () { return m_units.size(); }
    void getUnitList (std::vector<int>& list);
private:
    UnitMap  m_units;
};

#endif 
