#include <gtest/gtest.h>
#include <event.h>
#include <event_manager.h>
#include "game_engine_mock.h"
#include "base_system_mock.h"

TEST (EventManager, RaisedEventGetsProcessed)
{
    EventManager    manager;
    GameEngineMock  engine;
    BaseSystemMock  handler;
    Event*          event = new Event (EVENT_INVALID);

    EXPECT_CALL (handler, handleEvent(event));

    manager.initialise (&engine);
    manager.registerHandler (&handler);
    manager.raiseEvent (event);
    manager.processEvents();
}
