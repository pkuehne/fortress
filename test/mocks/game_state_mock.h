#pragma once


#include "../../src/core/game_state.h"
#include <gmock/gmock.h>

class GameStateMock : public GameState {
public:
    // GameStateMock() : GameState(nullptr, nullptr, nullptr) {}
    MOCK_METHOD1(isValidTile, bool(const Location&));
    MOCK_METHOD0(entities, const EntityHolder&());
    MOCK_METHOD0(components, ComponentManager*());
    MOCK_METHOD1(tile, Tile&(const Location&));
};


