#include <sprite_system.h>
#include <event.h>
#include <entity_manager.h>
#include "game_engine_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

// NW N NE // 1 2 3
// W  M  E // 4 5 6
// SW S SE // 7 8 9
TEST (SpriteSystem, AlignCornersThreeWaysAndMiddle)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    AddEntityEvent  l_event;
    EntityManager   l_entities;

    EXPECT_CALL (l_engine, raiseEvent(_)).Times (AtLeast (1));
    l_entities.initialise (&l_engine);
    Entity* l_entityNorthWest   = l_entities.createWallPrefab (1, 1);
    Entity* l_entityNorth       = l_entities.createWallPrefab (2, 1);
    Entity* l_entityNorthEast   = l_entities.createWallPrefab (3, 1);
    Entity* l_entityWest        = l_entities.createWallPrefab (1, 2);
    Entity* l_entityMiddle      = l_entities.createWallPrefab (2, 2);
    Entity* l_entityEast        = l_entities.createWallPrefab (3, 2);
    Entity* l_entitySouthWest   = l_entities.createWallPrefab (1, 3);
    Entity* l_entitySouth       = l_entities.createWallPrefab (2, 3);
    Entity* l_entitySouthEast   = l_entities.createWallPrefab (3, 3);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity = l_entityMiddle->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthEast)->sprite);

    l_event.entity = l_entityNorthWest->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthEast)->sprite);

    l_event.entity = l_entityNorthEast->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthEast)->sprite);

    l_event.entity = l_entitySouthWest->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthEast)->sprite);

    l_event.entity = l_entitySouthEast->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ (188, l_entities.getSprites()->get(l_entitySouthEast)->sprite);
}

//    E
// S SE
TEST (SpriteSystem, alignSouthEastbyItself)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    AddEntityEvent* l_event = new AddEntityEvent();
    EntityManager   l_entities;

    EXPECT_CALL (l_engine, raiseEvent(_)).Times (AtLeast (1));
    l_entities.initialise (&l_engine);

    Entity* l_entityEast        = l_entities.createWallPrefab (3,2);
    Entity* l_entitySouth       = l_entities.createWallPrefab (2,3);
    Entity* l_entitySouthEast   = l_entities.createWallPrefab (3,3);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event->entity = l_entitySouthEast->getId();
    l_system.handleEvent (l_event);

    EXPECT_EQ (210, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (198, l_entities.getSprites()->get(l_entitySouth)->sprite);
    EXPECT_EQ (188, l_entities.getSprites()->get(l_entitySouthEast)->sprite);
}

// NW N NE
// W     E
// SW S
TEST (SpriteSystem, allignEndsAndSideWalls)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    AddEntityEvent  l_event;
    EntityManager   l_entities;

    EXPECT_CALL (l_engine, raiseEvent(_)).Times (AtLeast (1));
    l_entities.initialise (&l_engine);

    Entity* l_entityNorthWest   = l_entities.createWallPrefab (1,1);
    Entity* l_entityNorth       = l_entities.createWallPrefab (2,1);
    Entity* l_entityNorthEast   = l_entities.createWallPrefab (3,1);
    Entity* l_entityWest        = l_entities.createWallPrefab (1,2);
    Entity* l_entityEast        = l_entities.createWallPrefab (3,2);
    Entity* l_entitySouthWest   = l_entities.createWallPrefab (1,3);
    Entity* l_entitySouth       = l_entities.createWallPrefab (2,3);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity = l_entityNorth->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouth)->sprite);

    l_event.entity = l_entityWest->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouth)->sprite);

    l_event.entity = l_entityEast->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (208, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ ('W', l_entities.getSprites()->get(l_entitySouth)->sprite);

    l_event.entity = l_entitySouth->getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(l_entityWest)->sprite);
    EXPECT_EQ (208, l_entities.getSprites()->get(l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(l_entitySouthWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(l_entitySouth)->sprite);

}

TEST (SpriteSystem, alignSingle)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    AddEntityEvent  l_event;
    EntityManager   l_entities;

    Entity          l_entityMiddle;
    l_entityMiddle.setId (5);
    l_entityMiddle.setName ("Wall");

    SpriteComponent l_spriteMiddle;
    l_spriteMiddle.xPos  = 2;
    l_spriteMiddle.yPos  = 2;
    l_spriteMiddle.sprite= 181;

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_entities.getSprites()->add (&l_entityMiddle,     l_spriteMiddle);

    l_event.entity = l_entityMiddle.getId();
    l_system.handleEvent (&l_event);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityMiddle)->sprite);

}

TEST (SpriteSystem, handleUnknownEvent)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    Event           l_event (EVENT_INVALID);

    l_system.initialise (&l_engine);
    l_system.handleEvent (&l_event);
}
