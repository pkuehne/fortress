#include "entity.h"


bool operator< (const Entity& lhs, const Entity& rhs) {
    return lhs.getId() < rhs.getId();
}

bool Entity::hasTag (Tag tag) {
    std::set<Tag>::iterator it = m_tags.find(tag);
    return it != m_tags.end();
}
