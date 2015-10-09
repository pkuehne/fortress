#ifndef __EVENT_H__
#define __EVENT_H__

#include <map>
#include <iostream>
#include "entity.h"
#include "utility.h"

typedef enum {
    EVENT_INVALID           = 0,
    EVENT_ADD_ENTITY        ,
    EVENT_REMOVE_ENTITY     ,
    EVENT_MOVE_ENTITY       ,
    EVENT_CHANGE_LOCATION   ,
    EVENT_ATTACK_ENTITY     ,
    EVENT_CHANGE_LEVEL      ,
    EVENT_DROP_EQUIPMENT    ,
    EVENT_PICKUP_EQUIPMENT  ,
    EVENT_EQUIP_ITEM        ,
    EVENT_UNEQUIP_ITEM      ,
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
    Location    newLocation;
};

class ChangeLocationEvent : public Event {
public:
    ChangeLocationEvent() : Event (EVENT_CHANGE_LOCATION) { }
    EntityId    entity;
    Location    oldLocation;
    Location    newLocation;
};

class AttackEntityEvent : public Event {
public:
    AttackEntityEvent () : Event (EVENT_ATTACK_ENTITY) { }
    EntityId    attacker;
    EntityId    defender;
    EntityId    weapon;
};

// Deprecated
class ChangeLevelEvent : public Event {
public:
    ChangeLevelEvent () : Event (EVENT_CHANGE_LEVEL) { }
    unsigned int    level;
    STAIR           direction;
};

class DropEquipmentEvent : public Event {
public:
    DropEquipmentEvent () : Event (EVENT_DROP_EQUIPMENT) { }
    EntityId        entity;
    EntityId        item;
};

class PickupEquipmentEvent : public Event {
public:
    PickupEquipmentEvent () : Event (EVENT_PICKUP_EQUIPMENT) { }
    EntityId        entity;
    EntityId        item;
};

class EquipItemEvent : public Event {
public:
    EquipItemEvent () : Event (EVENT_EQUIP_ITEM) { }
    EntityId        entity;
    EntityId        item;
};

class UnequipItemEvent : public Event {
public:
    UnequipItemEvent () : Event (EVENT_UNEQUIP_ITEM) { }
    EntityId        entity;
    EntityId        item;
};

#endif
