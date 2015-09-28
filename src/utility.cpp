#include "utility.h"
#include <cstdlib>

namespace Utility {

unsigned int randBetween (unsigned int start, unsigned int end)
{
    return ((rand() % (end-start)) + start);
}

bool randChance (unsigned int percentage)
{
    if (percentage>100) {
        std::cout << "randChance percentage must be <100!";
        return true;
    }

    return (randBetween (1, 100) < percentage);
}

}; // Close namespace

std::ostream& operator<< (std::ostream& out, const Location& loc)
{
    out << "(" << loc.x << "," << loc.y << "," << loc.z << ")";
    return out;
}
