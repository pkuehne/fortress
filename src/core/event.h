#pragma once

#include "entity.h"
#include "location.h"
#include "utility.h"
#include "window.h"
#include <iostream>
#include <memory>

class Event {
public:
    virtual ~Event() = default;
    virtual size_t type_id() { return typeid(*this).hash_code(); }
};

class AddEntityEvent : public Event {
public:
    AddEntityEvent(EntityId e, Location l) : entity(e), location(l) {}
    EntityId entity = 0;
    Location location;
};

class RemoveEntityEvent : public Event {
public:
    RemoveEntityEvent(EntityId e, Location l) : entity(e), location(l) {}
    EntityId entity = 0;
    Location location;
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

class KillEntityEvent : public Event {
public:
    explicit KillEntityEvent(EntityId e) : entity(e) {}
    EntityId entity = 0;
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
    explicit AddLogMessageEvent(const std::string& m,
                                const std::string& c = "info")
        : message(m), category(c) {}
    std::string message;
    std::string category;
};

class RegisterWindowEvent : public Event {
public:
    enum class WindowAction { None, Add, Replace, ReplaceAll };

    explicit RegisterWindowEvent(std::unique_ptr<Window> w, WindowAction a)
        : window(std::move(w)), action(a) {}

    mutable std::unique_ptr<Window> window;
    WindowAction action = WindowAction::None;
};

template <class T> class AddWindowEvent : public RegisterWindowEvent {
public:
    template <class... Args>
    explicit AddWindowEvent(Args&&... args)
        : RegisterWindowEvent(std::make_unique<T>(args...), WindowAction::Add) {
    }

    size_t type_id() override {
        return typeid(RegisterWindowEvent).hash_code();
    }
};

template <class T> class ReplaceWindowEvent : public RegisterWindowEvent {
public:
    template <class... Args>
    explicit ReplaceWindowEvent(Args&&... args)
        : RegisterWindowEvent(std::make_unique<T>(args...),
                              WindowAction::Replace) {}

    size_t type_id() override {
        return typeid(RegisterWindowEvent).hash_code();
    }
};

template <class T> class ReplaceAllWindowsEvent : public RegisterWindowEvent {
public:
    template <class... Args>
    explicit ReplaceAllWindowsEvent(Args&&... args)
        : RegisterWindowEvent(std::make_unique<T>(args...),
                              WindowAction::ReplaceAll) {}

    size_t type_id() override {
        return typeid(RegisterWindowEvent).hash_code();
    }
};

class CloseWindowEvent : public Event {
public:
    CloseWindowEvent() = default;
};

class UpdateExperienceEvent : public Event {
public:
    UpdateExperienceEvent(EntityId e, unsigned int x)
        : entity(e), experience(x) {}
    EntityId entity = 0;
    unsigned int experience = 0;
};

class LevelUpEvent : public Event {
public:
    LevelUpEvent(EntityId e, unsigned int l) : entity(e), level(l) {}
    EntityId entity = 0;
    unsigned int level = 0;
};

class QuitEvent : public Event {
public:
    QuitEvent() = default;
};

class EndTurnEvent : public Event {
public:
    EndTurnEvent() = default;
};

class UpdateTileSizeEvent : public Event {
public:
    explicit UpdateTileSizeEvent(int a) : adjustment(a) {}
    int adjustment = 0;
};

class ResizeWindowsEvent : public Event {
public:
    ResizeWindowsEvent() {}
};

class MapGeneratedEvent : public Event {
public:
    MapGeneratedEvent() {}
};

class GenerateRuralMapEvent : public Event {
public:
    GenerateRuralMapEvent(unsigned int h, unsigned int w, unsigned int d,
                          unsigned int r)
        : height(h), width(w), depth(d), rooms(r) {}

public:
    unsigned int height = 0;
    unsigned int width = 0;
    unsigned int depth = 0;
    unsigned int rooms = 0;
};

class UnlockEntityEvent : public Event {
public:
    UnlockEntityEvent(EntityId k, EntityId l) : key(k), lock(l) {}
    EntityId key = 0;
    EntityId lock = 0;
};

class LockEntityEvent : public Event {
public:
    LockEntityEvent(EntityId k, EntityId l) : key(k), lock(l) {}
    EntityId key = 0;
    EntityId lock = 0;
};