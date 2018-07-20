#include "utility.h"
#include <glog/logging.h>
#include <random>

namespace Utility {

unsigned int randBetween(unsigned int start, unsigned int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);

    return dis(gen);
}

bool randChance(unsigned int percentage) {
    if (percentage > 100) {
        LOG(ERROR) << "randChance percentage must be <100!";
        return true;
    }

    return (randBetween(1, 100) < percentage);
}

} // namespace Utility
