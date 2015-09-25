#include "utility.h"

namespace Utility {


};

std::ostream& operator<< (std::ostream& out, const Location& loc)
{
    out << "(" << loc.x << "," << loc.y << "," << loc.z << ")";
    return out;
}
