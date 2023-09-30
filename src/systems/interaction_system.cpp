#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/key_component.h"
#include "../components/openable_component.h"

void InteractionSystem::registerHandlers() {
    events()->subscribe<OpenEntityEvent>(
        [=](auto event) { handleOpenEntityEvent(event); });
    events()->subscribe<CloseEntityEvent>(
        [=](auto event) { handleCloseEntityEvent(event); });
    events()->subscribe<LockEntityEvent>(
        [=](auto event) { handleLockEntityEvent(event); });
    events()->subscribe<UnlockEntityEvent>(
        [=](auto event) { handleUnlockEntityEvent(event); });
}

void InteractionSystem::handleOpenEntityEvent(const OpenEntityEvent& event) {
    auto entity = entities()->world().entity(event.entity);

    auto openable = entity.get_mut<OpenableComponent>();
    if (openable->locked) {
        events()->fire<AddLogMessageEvent>("It's locked");
        return;
    }

    openable->open = true;
    entity.remove<ColliderComponent>();
}

void InteractionSystem::handleCloseEntityEvent(const CloseEntityEvent& event) {
    auto entity = entities()->world().entity(event.entity);

    entity.get_mut<OpenableComponent>()->open = false;
    entity.add<ColliderComponent>();
}

void InteractionSystem::handleLockEntityEvent(const LockEntityEvent& event) {
    auto lock = entities()->world().entity(event.lock);
    auto key = entities()->world().entity(event.key);

    if (!lock.has<OpenableComponent>()) {
        return;
    }
    if (!key.has<KeyComponent>()) {
        return;
    }
    lock.get_mut<OpenableComponent>()->locked = true;
}

void InteractionSystem::handleUnlockEntityEvent(
    const UnlockEntityEvent& event) {
    auto lock = entities()->world().entity(event.lock);
    auto key = entities()->world().entity(event.key);

    if (!lock.has<OpenableComponent>()) {
        return;
    }
    if (!key.has<KeyComponent>()) {
        return;
    }
    lock.get_mut<OpenableComponent>()->locked = false;
}