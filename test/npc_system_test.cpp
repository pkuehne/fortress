#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <game_engine_mock.h>
#include <game_state_mock.h>
#include <npc_system.h>

using namespace ::testing;

class NpcSystemTest : public ::testing::Test
{
public:
    NpcSystemTest() {}

    void SetUp() {
        EXPECT_CALL(engine, state()).WillRepeatedly(Return(&state));
        system.initialise(&engine);
    }
    void TearDown() { }

    NpcSystem       system;
    GameStateMock   state;
    GameEngineMock  engine;
};

TEST_F (NpcSystemTest, onPlayerTurnDoNothing)
{
    EXPECT_CALL(engine, isPlayerTurn()).WillOnce(Return(true));
    EXPECT_CALL(engine, state()).Times(0);

    system.update();
}

TEST_F (NpcSystemTest, updateLoopsThroughAllNpc)
{
    EXPECT_CALL(engine, isPlayerTurn()).WillOnce(Return(false));

    EntityId entity = 12345;
    EntityHolder entities;
    entities.insert(entity);
    EXPECT_CALL(state, entities()).WillOnce(ReturnRef(entities));

    system.update();
}
