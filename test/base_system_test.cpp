#include <game_system_base.h>
#include "game_engine_mock.h"
#include <entity_manager.h>
#include <gtest/gtest.h>

using namespace ::testing;

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

/*
TEST (GameSystemBase, findEntitiesAt)
{
    GameSystemBase  l_base;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    EntityId        l_entityMiddle = 3;
    SpriteComponent l_spriteMiddle;
    LocationComponent   l_locationMiddle;
    l_locationMiddle.x  = 2;
    l_locationMiddle.y  = 2;
    l_spriteMiddle.sprite= 181;

    EntityId        l_entityNorth;
    SpriteComponent l_spriteNorth;
    LocationComponent l_locationNorth;
    l_locationNorth.x  = 2;
    l_locationNorth.y  = 1;
    l_spriteNorth.sprite= 181;

    l_entities.getSprites()->add (l_entityMiddle,  l_spriteMiddle);
    l_entities.getSprites()->add (l_entityNorth,   l_spriteNorth);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));

    l_base.initialise (&l_engine);

    std::vector<EntityId> l_return = l_base.findEntitiesAt (2, 2);
    ASSERT_EQ (1, l_return.size());
    EXPECT_EQ (5, l_return[0]);
}

TEST (GameSystemBase, findEntitiesToThe)
{
    GameSystemBase  l_base;
    GameEngineMock  l_engine;
    MoveEntityEvent l_event;
    EntityManager   l_entities;

    Entity          l_entityMiddle;
    l_entityMiddle.setId (5);
    l_entityMiddle.setName ("Player");
    SpriteComponent l_spriteMiddle;
    l_spriteMiddle.xPos  = 2;
    l_spriteMiddle.yPos  = 2;
    l_spriteMiddle.sprite= 181;

    Entity          l_entityNorth;
    l_entityNorth.setId (6);
    l_entityNorth.setName ("Orc");
    SpriteComponent l_spriteNorth;
    l_spriteNorth.xPos  = 2;
    l_spriteNorth.yPos  = 1;
    l_spriteNorth.sprite= 181;

    l_entities.getSprites()->add (l_entityMiddle.getId(),  l_spriteMiddle);
    l_entities.getSprites()->add (l_entityNorth.getId(),   l_spriteNorth);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));

    l_base.initialise (&l_engine);

    std::vector<EntityId> l_return = l_base.findEntitiesToThe (Direction::North, &l_entityMiddle);
    ASSERT_EQ (1, l_return.size());
    EXPECT_EQ (6, l_return[0]);

}
*/