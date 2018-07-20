#include "../../src/core/entity_manager.h"
#include "../mocks/component_manager_mock.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/game_state_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class EntityManager_addEntity : public ::testing::Test {};

TEST_F(EntityManager_addEntity, addsEntityforAllList) {
    // Given
    EntityId entity = 1234;
    Location location;

    EntityManager manager;
    GameEngineMock mock;
    manager.initialise(&mock);

    // When
    manager.addEntity(entity, location);

    // Then
    ASSERT_EQ(1, manager.all().size());
}

class EntityManager_destroyEntity : public ::testing::Test {};

TEST_F(EntityManager_destroyEntity, addsEntityforAllList) {
    // Given
    EntityId entity = 1234;
    Location location;

    EntityManager manager;
    GameEngineMock mock;
    GameStateMock state;
    ComponentManagerMock components;

    EXPECT_CALL(state, components()).WillRepeatedly(Return(&components));
    EXPECT_CALL(mock, state()).WillRepeatedly(Return(&state));
    manager.initialise(&mock);
    manager.addEntity(entity, location);

    // When
    manager.destroyEntity(entity);

    // Then
    ASSERT_EQ(0, manager.all().size());
}
