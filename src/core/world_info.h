#pragma once

#include <map>

class Faction {
public:
    Faction() = default;
    ~Faction() = default;

    /// @brief Constructs a new faction with the given name
    /// @param[in] name The name of the faction
    explicit Faction(const std::string& name);

    /// @brief Provides the name of the faction
    const std::string& getName() const { return m_name; }

    /// @brief Sets the relationship to the given faction
    /// @param[in] other The other party to set the relationship for
    /// @param[in] relationship Absolute value to set the relationship to
    ///                         Ranges between -100 and 100;
    void setRelationship(const std::string& other, int relationship);

    /// @brief Return the value of the relationship to the other party
    /// @param[in] other The other party to get the relationship for
    /// @returns The value of the relationship in the range (-100, 100)
    int getRelationship(const std::string& other) const;

    /// @brief Sets the relationship to apply by default to other factions
    /// @param[in] relationship The default to apply
    void setDefaultRelationship(int relationship);

private:
    std::string m_name;
    std::map<std::string, int> m_relationships;
    int m_defaultRelationship = 0;
};

/// @brief Stores the abstract concepts present in the world
class WorldInfo {
public:
    WorldInfo() = default;
    ~WorldInfo() = default;

    /// @brief Get all factions in the world
    const std::map<std::string, Faction>& getFactions() const {
        return m_factions;
    }

    /// @brief Adds a new faction to the world
    /// @param[in] faction The faction to add
    /// @note Overwrites any existing faction with that name
    void addFaction(const Faction& faction) {
        m_factions[faction.getName()] = faction;
    }

private:
    std::map<std::string, Faction> m_factions;
};