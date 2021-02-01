#include "../../src/systems/npc_system.h"
#include "../mocks/entity_manager_mock.h"
#include "../mocks/game_engine_mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

// class NpcSystemTest : public ::testing::Test {
// public:
//     NpcSystemTest() {}

//     void SetUp() {
//         EXPECT_CALL(state,
//         entityManager()).WillRepeatedly(Return(&entities));
//         EXPECT_CALL(engine, state()).WillRepeatedly(Return(&state));
//         system.initialise(&engine);
//     }
//     void TearDown() {}

//     NpcSystem system;
//     GameStateMock state;
//     GameEngineMock engine;
//     EntityManagerMock entities;
// };

// TEST_F(NpcSystemTest, updateLoopsThroughAllNpc) {
//     EXPECT_CALL(engine, isPlayerTurn()).WillOnce(Return(false));

//     EntityId entity = 12345;
//     EntityHolder entities;
//     entities.insert(entity);
//     EXPECT_CALL(state, entities()).WillOnce(ReturnRef(entities));

//     system.onTurn();
// }
