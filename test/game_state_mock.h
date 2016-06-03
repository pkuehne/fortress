#ifndef __GAME_STATE_MOCK_H__
#define __GAME_STATE_MOCK_H__

#include "game_state.h"
#include <gmock/gmock.h>

class GameStateMock : public GameState {
public: 
    MOCK_METHOD1 (isValidTile, bool (const Location&));
};

#endif
