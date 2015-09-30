#include "utility.h"
#include <cstdlib>

namespace Utility {

unsigned int randBetween (unsigned int start, unsigned int end)
{
    static unsigned int seed = 0;

    if (seed == 0) {
        seed = time(nullptr);
        srand (seed);
        std::cout << "Created with seed " << seed << std::endl;
    }

    return ((rand() % (end-start+1)) + start);
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
