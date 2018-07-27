#pragma once

#include "grouping.h"
#include <map>

class GroupingManager {
public:
    GroupingManager() = default;
    virtual ~GroupingManager() = default;

private:
    std::map<std::string, Grouping> m_groupings;
};