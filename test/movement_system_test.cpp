#include <movement_system.h>
#include <entity_manager.h>
#include <gtest/gtest.h>
#include "game_engine_mock.h"

using namespace ::testing;

TEST (MovementSystem, handleEvent)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    EXPECT_CALL (l_engine, raiseEvent(_)).Times(4);
    EXPECT_CALL (l_engine, getLevel()).WillRepeatedly (Return (1));
    l_system.initialise (&l_engine);
    l_entities.initialise (&l_engine);
    EntityId        l_entityMiddle = l_entities.createEnemyPrefab (2, 2);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));

    l_event.entity      = l_entityMiddle;

    l_event.direction   = Direction::North;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (1, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->x);

    l_event.direction   = Direction::South;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->x);

    l_event.direction   = Direction::East;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (3, l_entities.getLocations()->get(l_entityMiddle)->x);

    l_event.direction   = Direction::West;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->x);

    l_event.direction   = Direction::None;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->x);

}

TEST (MovementSystem, CollidersBlockMovement)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    EXPECT_CALL (l_engine, raiseEvent(_)).Times(2);
    EXPECT_CALL (l_engine, getLevel()).WillRepeatedly (Return (1));

    l_system.initialise (&l_engine);
    l_entities.initialise (&l_engine);

    EntityId        l_entityMiddle = l_entities.createWallPrefab (2, 2);
    EntityId        l_entityOther = l_entities.createWallPrefab (3, 2);

    l_event.entity      = l_entityMiddle;

    l_event.direction   = Direction::East;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_EQ (2, l_entities.getLocations()->get(l_entityMiddle)->x);
    EXPECT_EQ (l_entities.getLocations()->get(l_entityOther)->y, l_entities.getLocations()->get(l_entityMiddle)->y);
    EXPECT_NE (l_entities.getLocations()->get(l_entityOther)->x, l_entities.getLocations()->get(l_entityMiddle)->x);


}

TEST (MovementSystem, handleUnknownEvent)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    Event           l_event (EVENT_INVALID);

    l_system.initialise (&l_engine);
    l_system.handleEvent (&l_event);
}
