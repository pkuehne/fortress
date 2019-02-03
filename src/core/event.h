#pragma once

#include "entity.h"
#include "location.h"
#include "utility.h"
#include <iostream>
#include <memory>

class Window;

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
    EntityId entity = 0;
    std::string prefab;
};

class PrefabCreatedEvent : public Event {
public:
    PrefabCreatedEvent(EntityId e, const std::string& p)
        : entity(e), prefab(p) {}
    EntityId entity = 0;
    std::string prefab;
};

class AddLogMessageEvent : public Event {
public:
    AddLogMessageEvent(const std::string& m, const std::string& c = "info")
        : message(m), category(c) {}
    std::string message;
    std::string category;
};

class RegisterWindowEvent : public Event {
public:
    enum class WindowAction { None, Add, Replace, ReplaceAll };

    RegisterWindowEvent(std::shared_ptr<Window> w,
                        WindowAction a = WindowAction::Add)
        : window(w), action(a) {}
    std::shared_ptr<Window> window = nullptr;
    WindowAction action = WindowAction::None;
};

class CloseWindowEvent : public Event {
public:
    CloseWindowEvent() = default;
};

class UpdateExperienceEvent : public Event {
public:
    UpdateExperienceEvent(EntityId e, unsigned int x)
        : entity(e), experience(x) {}
    EntityId entity;
    unsigned int experience;
};

class LevelUpEvent : public Event {
public:
    LevelUpEvent(EntityId e, unsigned int l) : entity(e), level(l) {}
    EntityId entity;
    unsigned int level;
};