#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <set>
#include <string>

typedef enum {
    PLAYER,
    MONSTER,
    WALL
} Tag;

typedef unsigned long EntityId;

class Entity {
friend class EntityManager;
public:
    void addTag (Tag tag) { m_tags.insert (tag); }
    std::set<Tag> getTags() { return m_tags; }
    bool hasTag(Tag tag);
    void setId (EntityId id) { m_id = id; }
    EntityId getId () const { return m_id; }

    void setName (const std::string& name) { m_name = name; }
    const std::string& getName () const { return m_name; }
private:
    EntityId        m_id;
    std::string     m_name;
    std::set<Tag>   m_tags;
};

bool operator< (const Entity& lhs, const Entity& rhs);

#endif
