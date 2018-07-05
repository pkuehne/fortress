#ifndef __QUEST_H__
#define __QUEST_H__

#include "entity.h"
#include <string>

class GameState;

class Quest {
public:
    explicit Quest(EntityId owner) : m_owner(owner){};
    virtual ~Quest() {}

    virtual bool& isCompleted() { return m_completed; }
    virtual bool& isFailed() { return m_failed; }
    virtual EntityId& owner() { return m_owner; }
    virtual std::string& title() { return m_title; }

    virtual void update(GameState& state) {}

private:
    EntityId m_owner = 0;
    bool m_completed = false;
    bool m_failed = false;
    std::string m_title = "A quest";
};

class KillQuest : public Quest {
public:
    explicit KillQuest(EntityId owner, EntityId target)
        : Quest(owner), m_target(target) {}

    virtual void update(GameState& state);

private:
    EntityId m_target;
};

#endif
