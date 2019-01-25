#pragma once

#include "entity.h"
#include "location.h"
#include "utility.h"
#include <iostream>
#include <map>

class Event {
public:
    virtual ~Event() = default;
};

class AddEntityEvent : public Event {
public:
    explicit AddEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
};

class RemoveEntityEvent : public Event {
public:
    explicit RemoveEntityEvent(EntityId e) : entity(e) {}
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
    explicit OpenEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
};

class CloseEntityEvent : public Event {
public:
    explicit CloseEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
};

class StartConversationEvent : public Event {
public:
    StartConversationEvent(EntityId i, EntityId t)
        : initiatedBy(i), target(t) {}
    EntityId initiatedBy = 0;
    EntityId target = 0;
};

class ChooseDialogOptionEvent : public Event {
public:
    explicit ChooseDialogOptionEvent(unsigned int o) : option(o) {}
    unsigned int option = 0;
};

class EndConversationEvent : public Event {
public:
    EndConversationEvent() {}
};

class InstantiatePrefabEvent : public Event {
public:
    InstantiatePrefabEvent(EntityId e, const std::string& p)
        : entity(e), prefab(p) {}
    EntityId entity;
    std::string prefab;
};

class PrefabCreatedEvent : public Event {
public:
    PrefabCreatedEvent(EntityId e, const std::string& p)
        : entity(e), prefab(p) {}
    EntityId entity;
    std::string prefab;
};

class CreateMapWindowEvent : public Event {
public:
    CreateMapWindowEvent() {}
};