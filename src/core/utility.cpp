#include "utility.h"
#include <cstdlib>
#include <glog/logging.h>

namespace Utility {

unsigned int randBetween(unsigned int start, unsigned int end) {
    static unsigned int seed = 0;

    if (seed == 0) {
        seed = time(nullptr);
        srand(seed);
        LOG(INFO) << "Created with seed " << seed << std::endl;
    }

    return ((rand() % (end - start + 1)) + start);
}

bool randChance(unsigned int percentage) {
    if (percentage > 100) {
        LOG(ERROR) << "randChance percentage must be <100!";
        return true;
    }

    return (randBetween(1, 100) < percentage);
}

} // namespace Utility
