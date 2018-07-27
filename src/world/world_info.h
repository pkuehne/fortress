#pragma once

#include "grouping.h"
#include <map>

/// @brief Stores the abstract concepts present in the world
class WorldInfo {
public:
    WorldInfo() = default;
    ~WorldInfo() = default;

    /// @brief Get all groupings in the world
    const std::map<std::string, Grouping>& getGroupings() const {
        return m_groupings;
    }

    /// @brief Adds a new grouping to the world
    /// @param[in] grouping The grouping to add
    /// @note Overwrites any existing grouping with that name
    void addGrouping(const Grouping& grouping) {
        m_groupings[grouping.getName()] = grouping;
    }

private:
    std::map<std::string, Grouping> m_groupings;
};