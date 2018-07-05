#ifndef __GAME_ENGINE_MOCK_H__
#define __GAME_ENGINE_MOCK_H__

#include "../../src/core/game_engine.h"
#include <gmock/gmock.h>

class GameEngineMock : public GameEngine {
public:
    GameEngineMock() : GameEngine(nullptr) {}
    MOCK_METHOD0(state, GameState*());
    MOCK_METHOD0(initialise, void());
    MOCK_METHOD0(isPlayerTurn, bool());
};

#endif
