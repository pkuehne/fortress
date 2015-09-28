#include "utility.h"
#include <cstdlib>

namespace Utility {

unsigned int randBetween (unsigned int start, unsigned int end)
{
    return ((rand() % (end-start)) + start);
}

};

std::ostream& operator<< (std::ostream& out, const Location& loc)
{
    out << "(" << loc.x << "," << loc.y << "," << loc.z << ")";
    return out;
}
