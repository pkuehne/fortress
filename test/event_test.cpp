#include <gtest/gtest.h>
#include <event.h>

TEST (Event, BasicEvent)
{
    Event event (EVENT_INVALID);
    EXPECT_EQ (EVENT_INVALID, event.getType());
}

TEST (Event, AddEntityEvent)
{
    AddEntityEvent event;
    EXPECT_EQ (EVENT_ADD_ENTITY, event.getType());
}

TEST (Event, MoveEntityEvent)
{
    MoveEntityEvent event;
    EXPECT_EQ (EVENT_MOVE_ENTITY, event.getType());
}
