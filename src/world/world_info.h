#pragma once

#include <map>
#include <memory>

class GroupingManager;

/// @brief Stores the abstract concepts present in the world
class WorldInfo {
public:
    WorldInfo();
    virtual ~WorldInfo();

    /// @brief Get the grouping manager in the world
    virtual GroupingManager& getGroupings() { return *m_groupings; }

private:
    std::unique_ptr<GroupingManager> m_groupings;
};