#include "unit.h"

Unit::Unit ()
: m_type (UNIT_WARRIOR)
, m_x (1)
, m_y (1)
{

}

Unit::Unit (UNIT type, int x, int y)
: m_type (type)
, m_x (x)
, m_y (y)
{

}

int Unit::getNextPath() 
{
    int retval = 0;
    if (m_path.size() > 0) {
        retval = m_path.back();
        m_path.pop_back();
    }
    return retval;
}
