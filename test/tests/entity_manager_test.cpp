#include "../../src/core/entity_manager.h"
#include "../../src/core/event_manager.h"
#include "../mocks/component_manager_mock.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/game_state_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class EntityManager_createEntity : public ::testing::Test {};

TEST_F(EntityManager_createEntity, raisedAddEntityEvent) {
    // Given
    Location location;

    EntityManager manager;
    GameEngineMock mock;
    manager.initialise(&mock);

    // When
    manager.createEntity(location);

    // Then
    EXPECT_EQ(1, mock.events()->getEventQueueSize());
}

class EntityManager_addEntity : public ::testing::Test {
public:
    void SetUp() {
        EXPECT_CALL(mock, state()).WillRepeatedly(Return(&state));
        manager.initialise(&mock);
    }

protected:
    EntityManager manager;
    GameEngineMock mock;
    GameStateMock state;
    EntityId entity = 1234;
    Location location;
};

TEST_F(EntityManager_addEntity, addsEntityforAllList) {
    // When
    manager.addEntity(entity, location);

    // Then
    ASSERT_EQ(1, manager.all().size());
}

class EntityManager_destroyEntity : public ::testing::Test {
public:
    void SetUp() {
        EXPECT_CALL(mock, state()).WillRepeatedly(Return(&state));
        manager.initialise(&mock);
        manager.addEntity(entity, location);
    }

protected:
    EntityId entity = 1234;
    Location location;
    EntityManager manager;
    GameEngineMock mock;
    GameStateMock state;
    ComponentManagerMock components;
};

TEST_F(EntityManager_destroyEntity, addsEntityforAllList) {
    // Given

    // When
    manager.destroyEntity(entity);

    // Then
    ASSERT_EQ(0, manager.all().size());
}

TEST_F(EntityManager_destroyEntity, doesnotraiseanyevents) {
    // Given
    EXPECT_EQ(1, mock.events()->getEventQueueSize());

    // When
    manager.destroyEntity(entity);

    // Then
    EXPECT_EQ(1, mock.events()->getEventQueueSize());
}

class EntityManager_getsetLocation : public ::testing::Test {};

TEST_F(EntityManager_getsetLocation, raisedAddEntityEvent) {
    // Given
    Location location;
    EntityId entity = 1234;

    EntityManager manager;
    GameEngineMock mock;
    manager.initialise(&mock);

    // When
    manager.setLocation(entity, location);
    Location l = manager.getLocation(entity);

    // Then
    EXPECT_EQ(l, location);
}

TEST_F(EntityManager_getsetLocation, setDoesNothingForZeroEntity) {
    // Given
    Location location(1, 2, 3);
    EntityId entity = 0;

    EntityManager manager;
    GameEngineMock mock;
    manager.initialise(&mock);

    // When
    manager.setLocation(entity, location);
    Location l = manager.getLocation(entity);

    // Then
    EXPECT_NE(l, location);
}
