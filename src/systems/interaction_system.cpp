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
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event.entity);
    if (!openable) {
        return;
    }
    if (openable->locked) {
        events()->fire<AddLogMessageEvent>("It's locked");
        return;
    }
    openable->open = true;

    components()->remove<ColliderComponent>(event.entity);
}

void InteractionSystem::handleCloseEntityEvent(const CloseEntityEvent& event) {
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event.entity);
    if (!openable) {
        return;
    }
    openable->open = false;

    components()->make<ColliderComponent>(event.entity);
}

void InteractionSystem::handleLockEntityEvent(const LockEntityEvent& event) {
    auto openable = components()->get<OpenableComponent>(event.lock);
    if (!openable) {
        return;
    }
    auto keyable = components()->get<KeyComponent>(event.key);
    if (!keyable) {
        return;
    }
    openable->locked = true;
}

void InteractionSystem::handleUnlockEntityEvent(
    const UnlockEntityEvent& event) {
    auto openable = components()->get<OpenableComponent>(event.lock);
    if (!openable) {
        return;
    }
    auto keyable = components()->get<KeyComponent>(event.key);
    if (!keyable) {
        return;
    }
    openable->locked = false;
}