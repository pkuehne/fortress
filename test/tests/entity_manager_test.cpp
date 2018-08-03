#include "../../src/core/entity_manager.h"
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

    // Then
    EXPECT_CALL(mock, raiseEvent(Matcher<Event*>(_)));

    // When
    manager.createEntity(location);
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

TEST_F(EntityManager_addEntity, setsLocation) {
    // Given
    location = Location(1, 2, 3, 4);
    Tile tile;
    EXPECT_CALL(state, tile(_)).WillOnce(ReturnRef(tile));

    // When
    manager.addEntity(entity, location);

    // Then
    ASSERT_EQ(location, manager.getLocation(entity));
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

TEST_F(EntityManager_destroyEntity, raisesDeleteEvent) {
    // Given
    EXPECT_CALL(mock, raiseEvent(Matcher<Event*>(_)));

    // When
    manager.destroyEntity(entity);

    // Then
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
