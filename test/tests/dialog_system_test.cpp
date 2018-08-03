#include "../../src/systems/dialog_system.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/window_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class DialogSystemTest : public ::testing::Test {
public:
    void SetUp() {
        EXPECT_CALL(engine, getWindows()).WillOnce(Return(&windowManager));
        system.initialise(&engine);
    }
    GameEngineMock engine;
    WindowManagerMock windowManager;
    DialogSystem system;
};

TEST_F(DialogSystemTest, createsDialogWindow) {
    // Given
    EntityId player = 1234;
    EntityId target = 4321;
    EXPECT_CALL(windowManager, registerWindow(_));

    // When
    system.handleStartConversationEvent(
        std::make_shared<StartConversationEvent>(player, target));

    // Then
}