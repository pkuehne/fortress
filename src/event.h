#ifndef __EVENT_H__
#define __EVENT_H__

#include <map>
#include <iostream>
#include "entity.h"
#include "utility.h"

typedef enum {
    EVENT_INVALID           = 0,
    EVENT_ADD_ENTITY        = 1,
    EVENT_REMOVE_ENTITY     = 2,
    EVENT_MOVE_ENTITY       = 3,
    EVENT_ATTACK_ENTITY     = 4,
    EVENT_MAX
} EventType;

class Event {
public:
    Event (EventType type) : m_type (type) { }
    virtual ~Event() { }
    EventType getType () const { return m_type; }

protected:
    EventType       m_type;
};

class AddEntityEvent : public Event {
public:
    AddEntityEvent () : Event (EVENT_ADD_ENTITY) { }
    EntityId     entity;
};

class RemoveEntityEvent : public Event {
public:
    RemoveEntityEvent () : Event (EVENT_REMOVE_ENTITY) { }
    EntityId     entity;
};

class MoveEntityEvent : public Event {
public:
    MoveEntityEvent () : Event (EVENT_MOVE_ENTITY) { }
    EntityId    entity;
    DIRECTION   direction;
};

class AttackEntityEvent : public Event {
public:
    AttackEntityEvent () : Event (EVENT_ATTACK_ENTITY) { }
    EntityId        entity;
    DIRECTION       direction;
};

#endif
