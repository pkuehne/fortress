#pragma once

#include "entity.h"
#include "location.h"
#include "utility.h"
#include <iostream>
#include <map>

typedef enum {
    EVENT_INVALID = 0,
    EVENT_ADD_ENTITY,
    EVENT_REMOVE_ENTITY,
    EVENT_MOVE_ENTITY,
    EVENT_CHANGE_LOCATION,
    EVENT_ATTACK_ENTITY,
    EVENT_CHANGE_LEVEL,
    EVENT_DROP_EQUIPMENT,
    EVENT_PICKUP_EQUIPMENT,
    EVENT_EQUIP_ITEM,
    EVENT_UNEQUIP_ITEM,
    EVENT_CONSUME_ITEM,
    EVENT_OPEN_ENTITY,
    EVENT_CLOSE_ENTITY,
    EVENT_START_CONVERSATION,
    EVENT_CHOOSE_DIALOG_OPTION,
    EVENT_END_CONVERSATION,
    EVENT_MAX
} EventType;

class Event {
public:
    explicit Event(EventType type = EVENT_INVALID) : m_type(type) {}
    virtual ~Event() {}
    EventType getType() const { return m_type; }

protected:
    EventType m_type = EVENT_INVALID;
};

class AddEntityEvent : public Event {
public:
    explicit AddEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
};

class RemoveEntityEvent : public Event {
public:
    RemoveEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
};

class MoveEntityEvent : public Event {
public:
    MoveEntityEvent(EntityId e, Location l) : entity(e), newLocation(l) {}
    EntityId entity = 0;
    Location newLocation;
};

class ChangeLocationEvent : public Event {
public:
    ChangeLocationEvent(EntityId e, Location o, Location n)
        : entity(e), oldLocation(o), newLocation(n) {}
    EntityId entity = 0;
    Location oldLocation;
    Location newLocation;
};

class AttackEntityEvent : public Event {
public:
    AttackEntityEvent(EntityId a, EntityId d) : attacker(a), defender(d) {}
    EntityId attacker = 0;
    EntityId defender = 0;
};

class DropEquipmentEvent : public Event {
public:
    DropEquipmentEvent(EntityId e, EntityId i) : entity(e), item(i) {}
    EntityId entity = 0;
    EntityId item = 0;
};

class PickupEquipmentEvent : public Event {
public:
    PickupEquipmentEvent(EntityId e, EntityId i) : entity(e), item(i) {}
    EntityId entity = 0;
    EntityId item = 0;
};

class EquipItemEvent : public Event {
public:
    EquipItemEvent(EntityId e, EntityId i) : entity(e), item(i) {}
    EntityId entity = 0;
    EntityId item = 0;
};

class UnequipItemEvent : public Event {
public:
    UnequipItemEvent(EntityId e, EntityId i) : entity(e), item(i) {}
    EntityId entity = 0;
    EntityId item = 0;
};

class ConsumeItemEvent : public Event {
public:
    ConsumeItemEvent(EntityId e, EntityId i) : entity(e), item(i) {}
    EntityId entity = 0;
    EntityId item = 0;
};

class OpenEntityEvent : public Event {
public:
    OpenEntityEvent() : Event(EVENT_OPEN_ENTITY) {}
    EntityId entity = 0;
};

class CloseEntityEvent : public Event {
public:
    CloseEntityEvent() : Event(EVENT_CLOSE_ENTITY) {}
    EntityId entity = 0;
};

class StartConversationEvent : public Event {
public:
    StartConversationEvent(EntityId iniator, EntityId target)
        : Event(EVENT_START_CONVERSATION), initiatedBy(iniator),
          target(target) {}
    EntityId initiatedBy = 0;
    EntityId target = 0;
};

class ChooseDialogOptionEvent : public Event {
public:
    explicit ChooseDialogOptionEvent(unsigned int option)
        : Event(EVENT_CHOOSE_DIALOG_OPTION), option(option) {}
    unsigned int option = 0;
};

class EndConversationEvent : public Event {
public:
    EndConversationEvent() : Event(EVENT_END_CONVERSATION) {}
};
