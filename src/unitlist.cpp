#include "unitlist.h"
#include "unit.h"
#include "map.h"

UnitList::UnitList ()
: m_units ()
{

}

Unit& UnitList::getUnit (int id)
{
    UnitIter iter = m_units.find (id);
    if (iter != m_units.end()) return iter->second;

    return Unit();
}

void UnitList::getUnitList (std::vector<int>& list)
{
    UnitIter iter = m_units.begin();

    for (; iter != m_units.end(); iter++) 
    {
        list.push_back (iter->first); 
    }
}

void UnitList::removeUnit (int id) 
{
    UnitIter iter = m_units.find (id);
    if (iter == m_units.end()) return; // Weird, but OK
    m_units.erase (iter); 
}
