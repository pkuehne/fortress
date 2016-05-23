#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_state.h"

class GameStateTest : public ::testing::Test {
    public:
        void SetUp() {
        }

        GameState state;
};

TEST_F (GameStateTest, nextTurnAdvancesTurnNumber)
{
    EXPECT_EQ (0, state.getTurn());
    state.nextTurn();
    EXPECT_EQ (1, state.getTurn());
    state.nextTurn();
    EXPECT_EQ (2, state.getTurn());
}

TEST_F (GameStateTest, nextTurnSwapsPlayerTurn)
{
    EXPECT_TRUE (state.isPlayerTurn());
    state.nextTurn();
    EXPECT_FALSE (state.isPlayerTurn());
    state.nextTurn();
    EXPECT_TRUE (state.isPlayerTurn());
}
