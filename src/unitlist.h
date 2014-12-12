#ifndef __UNITLIST_H__
#define __UNITLIST_H__

#include "unit.h"
#include <vector>

typedef std::vector<Unit>   UnitVector;
typedef std::vector<Unit>::iterator UnitIter;

class UnitList {
public:
    UnitList();

    void        loadUnits() {}
    UnitVector& getUnits() { return m_units; }
    Unit&       getUnit (int u) { return m_units[u]; }
    
private:
    UnitVector  m_units;
};

#endif 
