#include "../../src/core/game_state.h"
#include "../mocks/map_manager_mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class GameStateTest : public ::testing::Test {
public:
    GameStateTest() : state(&map) {}

    void SetUp() {}

    MapManagerMock map;
    GameState state;
};

TEST_F(GameStateTest, nextTurnAdvancesTurnNumber) {
    EXPECT_EQ(0, state.turn());
    state.nextTurn();
    EXPECT_EQ(1, state.turn());
    state.nextTurn();
    EXPECT_EQ(2, state.turn());
}

TEST_F(GameStateTest, nextTurnSwapsPlayerTurn) {
    EXPECT_TRUE(state.isPlayerTurn());
    state.nextTurn();
    EXPECT_FALSE(state.isPlayerTurn());
    state.nextTurn();
    EXPECT_TRUE(state.isPlayerTurn());
}

TEST_F(GameStateTest, creatingGameStateWithNullptrThrows) {
    EXPECT_ANY_THROW(GameState(nullptr));
}

TEST_F(GameStateTest, mapReturnsParameter) { EXPECT_EQ(&map, state.map()); }
