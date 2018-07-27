#pragma once

#include <map>

class Grouping {
public:
    Grouping() = default;
    ~Grouping() = default;

    /// @brief Constructs a new grouping with the given name
    /// @param[in] name The name of the grouping
    explicit Grouping(const std::string& name);

    /// @brief Provides the name of the grouping
    const std::string& getName() const { return m_name; }

    /// @brief Sets the relationship to the given grouping
    /// @param[in] other The other party to set the relationship for
    /// @param[in] relationship Absolute value to set the relationship to
    ///                         Ranges between -100 and 100;
    void setRelationship(const std::string& other, int relationship);

    /// @brief Return the value of the relationship to the other party
    /// @param[in] other The other party to get the relationship for
    /// @returns The value of the relationship in the range (-100, 100)
    int getRelationship(const std::string& other) const;

    /// @brief Sets the relationship to apply by default to other groupings
    /// @param[in] relationship The default to apply
    void setDefaultRelationship(int relationship);

private:
    std::string m_name;
    std::map<std::string, int> m_relationships;
    int m_defaultRelationship = 0;
};
