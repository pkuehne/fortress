#include "../../src/systems/dialog_system.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/window_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class DialogSystemTest : public ::testing::Test {};

TEST_F(DialogSystemTest, createsDialogWindow) {
    // Given
    GameEngineMock engine;
    WindowManagerMock window;
    DialogSystem system;
    EXPECT_CALL(engine, getWindows()).WillOnce(Return(&window));
    EXPECT_CALL(window, registerWindow(_));
    system.initialise(&engine);

    EntityId player = 1234;
    EntityId target = 4321;

    // When
    system.handleStartConversationEvent(
        std::make_shared<StartConversationEvent>(player, target));

    // Then
}