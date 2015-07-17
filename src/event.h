#ifndef __EVENT_H__
#define __EVENT_H__

#include <map>
#include <iostream>
#include "entity.h"

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
    Entity*     entity;
};

class RemoveEntityEvent : public Event {
public:
    RemoveEntityEvent () : Event (EVENT_REMOVE_ENTITY) { }
    Entity*     entity;
};

class MoveEntityEvent : public Event {
public:
    enum DIRECTION {
        NONE    = 0,
        UP      = 1,
        RIGHT   = 2,
        DOWN    = 3,
        LEFT    = 4
    };

    MoveEntityEvent () : Event (EVENT_MOVE_ENTITY) { }
    Entity*         entity;
    enum DIRECTION  direction;
};

class AttackEntityEvent : public Event {
public:
    AttackEntityEvent () : Event (EVENT_ATTACK_ENTITY) { }
    Entity          entity;
};

#endif
