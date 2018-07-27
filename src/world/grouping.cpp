#include "grouping.h"

namespace {
void clampValue(int& value) {
    if (value > 100) {
        value = 100;
    } else if (value < -100) {
        value = -100;
    }
}
} // namespace

Grouping::Grouping(const std::string& name) : m_name(name) {
    //
}

void Grouping::setRelationship(const std::string& other, int relationship) {
    clampValue(relationship);
    m_relationships[other] = relationship;
}

int Grouping::getRelationship(const std::string& other) const {
    auto iter = m_relationships.find(other);
    if (iter == m_relationships.end()) {
        return m_defaultRelationship;
    }
    return iter->second;
}

void Grouping::setDefaultRelationship(int relationship) {
    clampValue(relationship);
    m_defaultRelationship = relationship;
}
