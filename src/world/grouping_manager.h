#pragma once

#include "grouping.h"
#include <map>
#include <memory>

typedef std::map<std::string, Grouping> GroupingContainer;

class GroupingManager {
public:
    GroupingManager() = default;
    virtual ~GroupingManager() = default;

    /// @brief Return all Groupings in the world
    GroupingContainer& getGroupings();

    /// @brief get a reference to a specific grouping
    /// @param[in] name The grouping to get
    Grouping& getGrouping(const std::string& name);

    /// @brief Add a new empty Grouping
    /// @param[in] name The name for the Grouping
    /// @preturns The newly created Grouping
    Grouping& createNewGrouping(const std::string& name);

    /// @brief Set the relationship from one group to another
    /// @param[in] from The group to set the relationship for
    /// @param[in] to The group to whom the relationship is set
    /// @param[in] relationship The value of the relationship
    void setRelationship(Grouping& from, Grouping& to, int relationship);

    /// @brief Set the relationship from one group to another
    /// @param[in] from The group to set the relationship for
    /// @param[in] to The group to whom the relationship is set
    /// @param[in] relationship The value of the relationship
    void setRelationship(const std::string& from, const std::string& to,
                         int relationship);

    /// @brief Add an entity to a group
    /// @param[in] entity The entity to add
    /// @param[in] name The grouping to add the entity to
    void addEntityToGrouping(EntityId entity, const std::string& name);

    /// @brief Removes the given entity from all groupings
    /// @param[in] id The id of the entity to remove
    void removeEntityFromAllGroupings(EntityId id);

private:
    GroupingContainer m_groupings;
};