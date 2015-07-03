#include <game_system_base.h>
#include "game_engine_mock.h"
#include <gtest/gtest.h>

TEST (GameSystemBase, initialiseSetsGameEngineRef)
{
    GameSystemBase base;
    GameEngineMock engine;

    EXPECT_EQ (static_cast<GameEngineInterface*>(0), base.getEngineRef());
    base.initialise (&engine);
    EXPECT_EQ (&engine, base.getEngineRef());
}

TEST (GameSystemBase, handleEventDoesNothing)
{
    GameSystemBase  base;
    Event*          event = new Event (EVENT_INVALID);

    EXPECT_NO_THROW (base.handleEvent(event));
}

TEST (GameSystemBase, updateDoesNothing)
{
    GameSystemBase  base;

    EXPECT_NO_THROW (base.update());
}
