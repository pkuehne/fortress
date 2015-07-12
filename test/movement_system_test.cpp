#include <movement_system.h>
#include <entity_manager.h>
#include <gtest/gtest.h>
#include "game_engine_mock.h"

using namespace ::testing;

TEST (MovementSystem, Create)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    Entity          l_entityMiddle;
    l_entityMiddle.setId (5);
    l_entityMiddle.setName ("Wall");
    SpriteComponent l_spriteMiddle;
    l_spriteMiddle.xPos  = 2;
    l_spriteMiddle.yPos  = 2;
    l_spriteMiddle.sprite= 181;

    l_entities.getSprites()->add (&l_entityMiddle,     l_spriteMiddle);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity      = &l_entityMiddle;

    l_event.direction   = MoveEntityEvent::UP;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (1, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->xPos);

    l_event.direction   = MoveEntityEvent::DOWN;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->xPos);

    l_event.direction   = MoveEntityEvent::RIGHT;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (3, l_entities.getSprites()->get(&l_entityMiddle)->xPos);

    l_event.direction   = MoveEntityEvent::LEFT;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->xPos);

    l_event.direction   = MoveEntityEvent::NONE;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->xPos);

}

TEST (MovementSystem, CollidersBlockMovement)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    Entity          l_entityMiddle;
    l_entityMiddle.setId (5);
    l_entityMiddle.setName ("Wall");
    SpriteComponent l_spriteMiddle;
    l_spriteMiddle.xPos  = 2;
    l_spriteMiddle.yPos  = 2;
    l_spriteMiddle.sprite= 181;
    ColliderComponent l_colliderMiddle;

    Entity          l_entityOther;
    l_entityOther.setId (5);
    l_entityOther.setName ("Wall");
    SpriteComponent l_spriteOther;
    l_spriteOther.xPos  = 3;
    l_spriteOther.yPos  = 2;
    l_spriteOther.sprite= 181;
    ColliderComponent l_colliderOther;

    l_entities.getSprites()->add (&l_entityMiddle,     l_spriteMiddle);
    l_entities.getColliders()->add (&l_entityMiddle,     l_colliderMiddle);
    l_entities.getSprites()->add (&l_entityOther,     l_spriteOther);
    l_entities.getColliders()->add (&l_entityOther,     l_colliderOther);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity      = &l_entityMiddle;

    l_event.direction   = MoveEntityEvent::RIGHT;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->yPos);
    EXPECT_EQ (2, l_entities.getSprites()->get(&l_entityMiddle)->xPos);
}

TEST (MovementSystem, handleUnknownEvent)
{
    MovementSystem  l_system;
    GameEngineMock  l_engine;
    Event           l_event (EVENT_INVALID);

    l_system.initialise (&l_engine);
    l_system.handleEvent (&l_event);
}
