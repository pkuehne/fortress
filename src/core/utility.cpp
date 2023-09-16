#include "utility.h"
#include <random>
#include <spdlog/spdlog.h>

namespace Utility {

unsigned int randBetween(unsigned int start, unsigned int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);

    return dis(gen);
}

bool randChance(unsigned int percentage) {
    if (percentage > 100) {
        spdlog::error("randChance percentage must be <100!");
        return true;
    }

    return (randBetween(1, 100) < percentage);
}

} // namespace Utility
