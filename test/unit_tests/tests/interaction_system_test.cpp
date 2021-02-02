#include "collider_component.h"
#include "component_manager.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "interaction_system.h"
#include "key_component.h"
#include "map_manager.h"
#include "openable_component.h"
#include <gtest/gtest.h>

using namespace ::testing;

class InteractionSystemTest : public ::testing::Test {
public:
    InteractionSystemTest() {
        eventManager = std::make_shared<EventManager>();
        componentManager = std::make_shared<ComponentManager>();
        entityManager = std::make_shared<EntityManager>();
        mapManager = std::make_shared<MapManager>();
    }

    void SetUp() {
        system.initialise(eventManager, componentManager, entityManager,
                          mapManager);
    }
    std::shared_ptr<EventManager> eventManager = nullptr;
    std::shared_ptr<ComponentManager> componentManager = nullptr;
    std::shared_ptr<EntityManager> entityManager = nullptr;
    std::shared_ptr<MapManager> mapManager = nullptr;
    InteractionSystem system;
};

TEST_F(InteractionSystemTest, handleOpenForOpenable) {
    // Given
    EntityId entity = 1234;
    auto openable = componentManager->make<OpenableComponent>(entity);
    auto collidable = componentManager->make<ColliderComponent>(entity);

    // When
    auto event = OpenEntityEvent(entity);
    system.handleOpenEntityEvent(event);

    // Then
    EXPECT_TRUE(openable->open);
    EXPECT_FALSE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleOpenForNonOpenable) {
    // Given
    EntityId entity = 1234;
    auto collidable = componentManager->make<ColliderComponent>(entity);

    // When
    auto event = OpenEntityEvent(entity);
    system.handleOpenEntityEvent(event);

    // Then
    EXPECT_TRUE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleOpenDoesNotWorkIfLocked) {
    // Given
    EntityId entity = 1234;
    auto openable = componentManager->make<OpenableComponent>(entity);
    auto collidable = componentManager->make<ColliderComponent>(entity);
    openable->locked = true;

    // When
    auto event = OpenEntityEvent(entity);
    system.handleOpenEntityEvent(event);

    // Then
    EXPECT_FALSE(openable->open);
    EXPECT_TRUE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleCloseForOpenable) {
    // Given
    EntityId entity = 1234;
    auto openable = componentManager->make<OpenableComponent>(entity);
    openable->open = true;

    // When
    auto event = CloseEntityEvent(entity);
    system.handleCloseEntityEvent(event);

    // Then
    EXPECT_FALSE(openable->open);
    EXPECT_TRUE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleCloseForOpenableIgnoresLocked) {
    // Given
    EntityId entity = 1234;
    auto openable = componentManager->make<OpenableComponent>(entity);
    openable->open = true;
    openable->locked = true;

    // When
    auto event = CloseEntityEvent(entity);
    system.handleCloseEntityEvent(event);

    // Then
    EXPECT_FALSE(openable->open);
    EXPECT_TRUE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleCloseForNonOpenable) {
    // Given
    EntityId entity = 1234;

    // When
    auto event = CloseEntityEvent(entity);
    system.handleCloseEntityEvent(event);

    // Then
    EXPECT_FALSE(componentManager->exists<ColliderComponent>(entity));
}

TEST_F(InteractionSystemTest, handleLockEntityEvent_locksLockableWithKey) {
    // Given
    EntityId key = 1234;
    EntityId lock = 9876;
    auto openable = componentManager->make<OpenableComponent>(lock);
    auto keyable = componentManager->make<KeyComponent>(key);
    openable->locked = false;

    // When
    auto event = LockEntityEvent(key, lock);
    system.handleLockEntityEvent(event);

    // Then
    EXPECT_TRUE(openable->locked);
}

TEST_F(InteractionSystemTest,
       handleLockEntityEvent_doesntlockLockableWithoutKey) {
    // Given
    EntityId key = 1234;
    EntityId lock = 9876;
    auto openable = componentManager->make<OpenableComponent>(lock);
    openable->locked = false;

    // When
    auto event = LockEntityEvent(key, lock);
    system.handleLockEntityEvent(event);

    // Then
    EXPECT_FALSE(openable->locked);
}

TEST_F(InteractionSystemTest, handleUnlockEntityEvent_unlocksLockableWithKey) {
    // Given
    EntityId key = 1234;
    EntityId lock = 9876;
    auto openable = componentManager->make<OpenableComponent>(lock);
    auto keyable = componentManager->make<KeyComponent>(key);
    openable->locked = true;

    // When
    auto event = UnlockEntityEvent(key, lock);
    system.handleUnlockEntityEvent(event);

    // Then
    EXPECT_FALSE(openable->locked);
}

TEST_F(InteractionSystemTest,
       handleUnlockEntityEvent_doesntunlockLockableWithitoutKey) {
    // Given
    EntityId key = 1234;
    EntityId lock = 9876;
    auto openable = componentManager->make<OpenableComponent>(lock);
    openable->locked = true;

    // When
    auto event = UnlockEntityEvent(key, lock);
    system.handleUnlockEntityEvent(event);

    // Then
    EXPECT_TRUE(openable->locked);
}
