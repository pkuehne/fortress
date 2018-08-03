#include "../../src/components/player_component.h"
#include "../../src/core/component_manager.h"
#include "../../src/systems/dialog_system.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/game_state_mock.h"
#include "../mocks/window_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class DialogSystemTest : public ::testing::Test {
public:
    void SetUp() {
        state.components()->make<PlayerComponent>(player);

        EXPECT_CALL(state, player()).WillRepeatedly(Return(player));
        EXPECT_CALL(engine, getWindows())
            .WillRepeatedly(Return(&windowManager));
        EXPECT_CALL(engine, state()).WillRepeatedly(Return(&state));

        system.initialise(&engine);
    }
    GameEngineMock engine;
    GameStateMock state;
    WindowManagerMock windowManager;
    ComponentManager componentManager;
    DialogSystem system;
    EntityId player = 1234;
};

TEST_F(DialogSystemTest, createsDialogWindow) {
    // Given
    EntityId target = 4321;
    EXPECT_CALL(windowManager, registerWindow(_));

    // When
    system.handleStartConversationEvent(
        std::make_shared<StartConversationEvent>(player, target));

    // Then
}

TEST_F(DialogSystemTest, throwsIfNoPlayerSet) {
    // Given
    EntityId target = 4321;
    state.components()->removeAll(player);

    // When
    EXPECT_THROW(system.handleStartConversationEvent(
                     std::make_shared<StartConversationEvent>(player, target)),
                 std::string);

    // Then
}

TEST_F(DialogSystemTest, setsInConversationWithToInitiatorIfNotPlayer) {
    // Given
    EntityId target = 4321;
    EXPECT_CALL(windowManager, registerWindow(_));

    // When
    system.handleStartConversationEvent(
        std::make_shared<StartConversationEvent>(target, player));

    // Then
    EXPECT_EQ(
        target,
        state.components()->get<PlayerComponent>(player)->inConversationWith);
}

TEST_F(DialogSystemTest, setsInConversationWithToTargetIfNotPlayer) {
    // Given
    EntityId target = 4321;
    EXPECT_CALL(windowManager, registerWindow(_));

    // When
    system.handleStartConversationEvent(
        std::make_shared<StartConversationEvent>(player, target));

    // Then
    EXPECT_EQ(
        target,
        state.components()->get<PlayerComponent>(player)->inConversationWith);
}
