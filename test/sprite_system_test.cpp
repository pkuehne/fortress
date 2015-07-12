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

    Entity          l_entityNorthWest;
    l_entityNorthWest.setId (1);
    l_entityNorthWest.setName ("Wall");
    Entity          l_entityNorth;
    l_entityNorth.setId (2);
    l_entityNorth.setName ("Wall");
    Entity          l_entityNorthEast;
    l_entityNorthEast.setId (3);
    l_entityNorthEast.setName ("Wall");
    Entity          l_entityWest;
    l_entityWest.setId (4);
    l_entityWest.setName ("Wall");
    Entity          l_entityMiddle;
    l_entityMiddle.setId (5);
    l_entityMiddle.setName ("Wall");
    Entity          l_entityEast;
    l_entityEast.setId (6);
    l_entityEast.setName ("Wall");
    Entity          l_entitySouthWest;
    l_entitySouthWest.setId (7);
    l_entitySouthWest.setName ("Wall");
    Entity          l_entitySouth;
    l_entitySouth.setId (8);
    l_entitySouth.setName ("Wall");
    Entity          l_entitySouthEast;
    l_entitySouthEast.setId (9);
    l_entitySouthEast.setName ("Wall");

    SpriteComponent l_spriteNorthWest;
    l_spriteNorthWest.xPos  = 1;
    l_spriteNorthWest.yPos  = 1;
    l_spriteNorthWest.sprite= 181;
    SpriteComponent l_spriteNorth;
    l_spriteNorth.xPos  = 2;
    l_spriteNorth.yPos  = 1;
    l_spriteNorth.sprite= 181;
    SpriteComponent l_spriteNorthEast;
    l_spriteNorthEast.xPos  = 3;
    l_spriteNorthEast.yPos  = 1;
    l_spriteNorthEast.sprite= 181;
    SpriteComponent l_spriteWest;
    l_spriteWest.xPos  = 1;
    l_spriteWest.yPos  = 2;
    l_spriteWest.sprite= 181;
    SpriteComponent l_spriteMiddle;
    l_spriteMiddle.xPos  = 2;
    l_spriteMiddle.yPos  = 2;
    l_spriteMiddle.sprite= 181;
    SpriteComponent l_spriteEast;
    l_spriteEast.xPos  = 3;
    l_spriteEast.yPos  = 2;
    l_spriteEast.sprite= 181;
    SpriteComponent l_spriteSouthWest;
    l_spriteSouthWest.xPos  = 1;
    l_spriteSouthWest.yPos  = 3;
    l_spriteSouthWest.sprite= 181;
    SpriteComponent l_spriteSouth;
    l_spriteSouth.xPos  = 2;
    l_spriteSouth.yPos  = 3;
    l_spriteSouth.sprite= 181;
    SpriteComponent l_spriteSouthEast;
    l_spriteSouthEast.xPos  = 3;
    l_spriteSouthEast.yPos  = 3;
    l_spriteSouthEast.sprite= 181;

    l_entities.getSprites()->add (&l_entityNorthWest,  l_spriteNorthWest);
    l_entities.getSprites()->add (&l_entityNorth,      l_spriteNorth);
    l_entities.getSprites()->add (&l_entityNorthEast,  l_spriteNorthEast);
    l_entities.getSprites()->add (&l_entityWest,       l_spriteWest);
    l_entities.getSprites()->add (&l_entityMiddle,     l_spriteMiddle);
    l_entities.getSprites()->add (&l_entityEast,       l_spriteEast);
    l_entities.getSprites()->add (&l_entitySouthWest,  l_spriteSouthWest);
    l_entities.getSprites()->add (&l_entitySouth,      l_spriteSouth);
    l_entities.getSprites()->add (&l_entitySouthEast,  l_spriteSouthEast);


    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity = &l_entityMiddle;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);

    l_event.entity = &l_entityNorthWest;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);

    l_event.entity = &l_entityNorthEast;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);

    l_event.entity = &l_entitySouthWest;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);

    l_event.entity = &l_entitySouthEast;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (203, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (204, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);
    EXPECT_EQ (185, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (202, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (188, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);
}

//    E
// S SE
TEST (SpriteSystem, alignSouthEastbyItself)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    AddEntityEvent  l_event;
    EntityManager   l_entities;

    Entity          l_entityEast;
    l_entityEast.setId (6);
    l_entityEast.setName ("Wall");
    Entity          l_entitySouth;
    l_entitySouth.setId (8);
    l_entitySouth.setName ("Wall");
    Entity          l_entitySouthEast;
    l_entitySouthEast.setId (9);
    l_entitySouthEast.setName ("Wall");

    SpriteComponent l_spriteEast;
    l_spriteEast.xPos  = 3;
    l_spriteEast.yPos  = 2;
    l_spriteEast.sprite= 181;
    SpriteComponent l_spriteSouth;
    l_spriteSouth.xPos  = 2;
    l_spriteSouth.yPos  = 3;
    l_spriteSouth.sprite= 181;
    SpriteComponent l_spriteSouthEast;
    l_spriteSouthEast.xPos  = 3;
    l_spriteSouthEast.yPos  = 3;
    l_spriteSouthEast.sprite= 181;

    l_entities.getSprites()->add (&l_entityEast,       l_spriteEast);
    l_entities.getSprites()->add (&l_entitySouth,      l_spriteSouth);
    l_entities.getSprites()->add (&l_entitySouthEast,  l_spriteSouthEast);


    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity = &l_entitySouthEast;
    l_system.handleEvent (&l_event);

    EXPECT_EQ (210, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (198, l_entities.getSprites()->get(&l_entitySouth)->sprite);
    EXPECT_EQ (188, l_entities.getSprites()->get(&l_entitySouthEast)->sprite);
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

    Entity          l_entityNorthWest;
    l_entityNorthWest.setId (1);
    l_entityNorthWest.setName ("Wall");
    Entity          l_entityNorth;
    l_entityNorth.setId (2);
    l_entityNorth.setName ("Wall");
    Entity          l_entityNorthEast;
    l_entityNorthEast.setId (3);
    l_entityNorthEast.setName ("Wall");
    Entity          l_entityWest;
    l_entityWest.setId (4);
    l_entityWest.setName ("Wall");
    Entity          l_entityEast;
    l_entityEast.setId (6);
    l_entityEast.setName ("Wall");
    Entity          l_entitySouthWest;
    l_entitySouthWest.setId (7);
    l_entitySouthWest.setName ("Wall");
    Entity          l_entitySouth;
    l_entitySouth.setId (8);
    l_entitySouth.setName ("Wall");

    SpriteComponent l_spriteNorthWest;
    l_spriteNorthWest.xPos  = 1;
    l_spriteNorthWest.yPos  = 1;
    l_spriteNorthWest.sprite= 181;
    SpriteComponent l_spriteNorth;
    l_spriteNorth.xPos  = 2;
    l_spriteNorth.yPos  = 1;
    l_spriteNorth.sprite= 181;
    SpriteComponent l_spriteNorthEast;
    l_spriteNorthEast.xPos  = 3;
    l_spriteNorthEast.yPos  = 1;
    l_spriteNorthEast.sprite= 181;
    SpriteComponent l_spriteWest;
    l_spriteWest.xPos  = 1;
    l_spriteWest.yPos  = 2;
    l_spriteWest.sprite= 181;
    SpriteComponent l_spriteEast;
    l_spriteEast.xPos  = 3;
    l_spriteEast.yPos  = 2;
    l_spriteEast.sprite= 181;
    SpriteComponent l_spriteSouthWest;
    l_spriteSouthWest.xPos  = 1;
    l_spriteSouthWest.yPos  = 3;
    l_spriteSouthWest.sprite= 181;
    SpriteComponent l_spriteSouth;
    l_spriteSouth.xPos  = 2;
    l_spriteSouth.yPos  = 3;
    l_spriteSouth.sprite= 181;

    l_entities.getSprites()->add (&l_entityNorthWest,  l_spriteNorthWest);
    l_entities.getSprites()->add (&l_entityNorth,      l_spriteNorth);
    l_entities.getSprites()->add (&l_entityNorthEast,  l_spriteNorthEast);
    l_entities.getSprites()->add (&l_entityWest,       l_spriteWest);
    l_entities.getSprites()->add (&l_entityEast,       l_spriteEast);
    l_entities.getSprites()->add (&l_entitySouthWest,  l_spriteSouthWest);
    l_entities.getSprites()->add (&l_entitySouth,      l_spriteSouth);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    l_event.entity = &l_entityNorth;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouth)->sprite);

    l_event.entity = &l_entityWest;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouth)->sprite);

    l_event.entity = &l_entityEast;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (208, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouth)->sprite);

    l_event.entity = &l_entitySouth;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (201, l_entities.getSprites()->get(&l_entityNorthWest)->sprite);
    EXPECT_EQ (205, l_entities.getSprites()->get(&l_entityNorth)->sprite);
    EXPECT_EQ (187, l_entities.getSprites()->get(&l_entityNorthEast)->sprite);
    EXPECT_EQ (186, l_entities.getSprites()->get(&l_entityWest)->sprite);
    EXPECT_EQ (208, l_entities.getSprites()->get(&l_entityEast)->sprite);
    EXPECT_EQ (200, l_entities.getSprites()->get(&l_entitySouthWest)->sprite);
    EXPECT_EQ (181, l_entities.getSprites()->get(&l_entitySouth)->sprite);


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

    l_event.entity = &l_entityMiddle;
    l_system.handleEvent (&l_event);
    EXPECT_EQ (206, l_entities.getSprites()->get(&l_entityMiddle)->sprite);

}

TEST (SpriteSystem, handleUnknownEvent)
{
    SpriteSystem    l_system;
    GameEngineMock  l_engine;
    Event           l_event (EVENT_INVALID);

    l_system.initialise (&l_engine);
    l_system.handleEvent (&l_event);
}
