#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/key_component.h"
#include "../components/openable_component.h"

void InteractionSystem::registerHandlers() {
    events()->subscribe<OpenEntityEvent>(
        [=](std::shared_ptr<OpenEntityEvent> event) {
            handleOpenEntityEvent(event);
        });
    events()->subscribe<CloseEntityEvent>(
        [=](std::shared_ptr<CloseEntityEvent> event) {
            handleCloseEntityEvent(event);
        });
    events()->subscribe<LockEntityEvent>(
        [=](std::shared_ptr<LockEntityEvent> event) {
            handleLockEntityEvent(event);
        });
    events()->subscribe<UnlockEntityEvent>(
        [=](std::shared_ptr<UnlockEntityEvent> event) {
            handleUnlockEntityEvent(event);
        });
}

void InteractionSystem::handleOpenEntityEvent(
    std::shared_ptr<OpenEntityEvent> event) {
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    if (openable->locked) {
        events()->raise(std::make_shared<AddLogMessageEvent>("It's locked"));
        return;
    }
    openable->open = true;

    components()->remove<ColliderComponent>(event->entity);
}

void InteractionSystem::handleCloseEntityEvent(
    std::shared_ptr<CloseEntityEvent> event) {
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    openable->open = false;

    components()->make<ColliderComponent>(event->entity);
}

void InteractionSystem::handleLockEntityEvent(
    std::shared_ptr<LockEntityEvent> event) {
    auto openable = components()->get<OpenableComponent>(event->lock);
    if (!openable) {
        return;
    }
    auto keyable = components()->get<KeyComponent>(event->key);
    if (!keyable) {
        return;
    }
    openable->locked = true;
}

void InteractionSystem::handleUnlockEntityEvent(
    std::shared_ptr<UnlockEntityEvent> event) {
    auto openable = components()->get<OpenableComponent>(event->lock);
    if (!openable) {
        return;
    }
    auto keyable = components()->get<KeyComponent>(event->key);
    if (!keyable) {
        return;
    }
    openable->locked = false;
}