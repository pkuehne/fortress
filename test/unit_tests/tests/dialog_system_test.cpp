#include "../../src/components/player_component.h"
#include "../../src/core/component_manager.h"
#include "../../src/core/entity_manager.h"
#include "../../src/systems/dialog_system.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/window_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class DialogSystemTest : public ::testing::Test {
public:
    DialogSystemTest() {
        eventManager = std::make_shared<EventManager>();
        componentManager = std::make_shared<ComponentManager>();
        entityManager = std::make_shared<EntityManager>();
        mapManager = std::make_shared<MapManager>();

        comp = componentManager->make<PlayerComponent>(player);
    }

    void SetUp() {
        system.initialise(eventManager, componentManager, entityManager,
                          mapManager);
    }
    WindowManagerMock windowManager;
    std::shared_ptr<EventManager> eventManager = nullptr;
    std::shared_ptr<ComponentManager> componentManager = nullptr;
    std::shared_ptr<EntityManager> entityManager = nullptr;
    std::shared_ptr<MapManager> mapManager = nullptr;
    DialogSystem system;
    EntityId player = 1234;
    PlayerComponent* comp = nullptr;
};

// TEST_F(DialogSystemTest, createsDialogWindow) {
//     // Given
//     EntityId target = 4321;
//     EXPECT_CALL(windowManager, registerWindow(_));

//     // When
//     system.handleStartConversationEvent(
//         std::make_shared<StartConversationEvent>(player, target));

//     // Then
// }

TEST_F(DialogSystemTest, throwsIfNoPlayerSet) {
    // // Given
    // EntityId target = 4321;
    // state.components()->removeAll(player);

    // // When
    // EXPECT_THROW(system.handleStartConversationEvent(
    //                  std::make_shared<StartConversationEvent>(player,
    //                  target)),
    //              std::string);

    //    // Then
}

// TEST_F(DialogSystemTest, setsInConversationWithToInitiatorIfNotPlayer) {
//     // Given
//     EntityId target = 4321;
//     EXPECT_CALL(windowManager, registerWindow(_));

//     // When
//     system.handleStartConversationEvent(
//         std::make_shared<StartConversationEvent>(target, player));

//     // Then
//     EXPECT_EQ(
//         target,
//         state.components()->get<PlayerComponent>(player)->inConversationWith);
// }

// TEST_F(DialogSystemTest, setsInConversationWithToTargetIfNotPlayer) {
//     // Given
//     EntityId target = 4321;
//     EXPECT_CALL(windowManager, registerWindow(_));

//     // When
//     system.handleStartConversationEvent(
//         std::make_shared<StartConversationEvent>(player, target));

//     // Then
//     EXPECT_EQ(
//         target,
//         state.components()->get<PlayerComponent>(player)->inConversationWith);
// }

TEST_F(DialogSystemTest, doesNotUpdateConversationTargetIfAlreadySet) {
    // // Given
    // EntityId target = 4321;
    // EntityId current = 5555;

    // EXPECT_CALL(windowManager, registerWindow(_)).Times(0);
    // state.components()->get<PlayerComponent>(player)->inConversationWith =
    //     current;

    // // When
    // system.handleStartConversationEvent(
    //     std::make_shared<StartConversationEvent>(player, target));

    // // Then
    // EXPECT_EQ(
    //     current,
    //     state.components()->get<PlayerComponent>(player)->inConversationWith);
}

TEST_F(DialogSystemTest, unsetsInConversationWithWhenConversationEnds) {
    // // Given

    // // When
    // system.handleEndConversationEvent(std::make_shared<EndConversationEvent>());

    // // Then
    // EXPECT_EQ(
    //     0,
    // state.components()->get<PlayerComponent>(player)->inConversationWith);
}

class DialogSystemTest_generateDialog : public DialogSystemTest {
public:
    void SetUp() {}
};

TEST_F(DialogSystemTest_generateDialog, setsTheDialogText) {
    // // Given

    // // When
    // system.generateDialog(comp);

    // // Then
    // EXPECT_NE(std::string(""), comp->dialogText);
}

TEST_F(DialogSystemTest_generateDialog, setsTheDialogOptions) {
    // // Given

    // // When
    // system.generateDialog(comp);

    // // Then
    // EXPECT_NE(0, comp->dialogOptions.size());
}

TEST_F(DialogSystemTest_generateDialog, clearsPreviousOptions) {
    // // Given
    // comp->dialogOptions.push_back("A");
    // comp->dialogOptions.push_back("B");

    // // When
    // system.generateDialog(comp);

    // // Then
    // EXPECT_NE("A", comp->dialogOptions[0]);
}