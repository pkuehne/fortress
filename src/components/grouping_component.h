#pragma once

#include "component_base.h"
#include <vector>

struct GroupingComponent : public ComponentBase {
    std::vector<std::string> groupings;
};