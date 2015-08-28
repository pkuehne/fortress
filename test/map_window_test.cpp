#include "map_window.h"
#include "game_engine_mock.h"
#include "entity_manager_mock.h"
#include "entity_manager.h"
#include "component_manager_mock.h"
#include "graphics_mock.h"
#include "event.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST (MapWindow, creatingLoadsMap)
{
    GameEngineMock  l_engine;
    MapWindow       l_win;

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);

    l_win.initialise (&l_engine);
}

TEST (MapWindow, redraw)
{
    GameEngineMock      l_engine;
    MapWindow           l_win;
    EntityManagerMock   l_entities;
    GraphicsMock        l_graphics;
    ComponentManager<SpriteComponent>   l_spriteComponents;
    ComponentManager<LocationComponent> l_locComponents;
    SpriteComponent     l_sprite;
    LocationComponent   l_loc;

    l_loc.y = 1;
    l_loc.x = 1;
    l_locComponents.add (1, l_loc);

    l_sprite.sprite = 180;
    l_spriteComponents.add (1, l_sprite);

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_engine, getGraphics()).Times(1).WillRepeatedly (Return (&l_graphics));
    EXPECT_CALL (l_entities, getSprites()).Times(1).WillOnce (Return (&l_spriteComponents));
    EXPECT_CALL (l_entities, getLocations()).Times(1).WillOnce (Return (&l_locComponents));
    EXPECT_CALL (l_graphics, drawTile(Eq(l_loc.y), Eq(l_loc.x), Eq(l_sprite.sprite), _, _)).Times(1);
    l_win.initialise (&l_engine);
    l_win.redraw();
    //FAIL() << "Not finished";
}

TEST (MapWindow, WASDMovesPlayer)
{
    MapWindow           l_win;
    GameEngineMock      l_engine;
    EntityManagerMock   l_entities;
    EntityId            l_entity = 1;
    MoveEntityEvent*    l_event = new MoveEntityEvent;

    l_event->entity     = l_entity;

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    EXPECT_CALL (l_engine, swapTurn()).Times(5);
    l_win.initialise (&l_engine);

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::North;
    l_win.keyDown ('w');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::South;
    l_win.keyDown ('s');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::West;
    l_win.keyDown ('a');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::East;
    l_win.keyDown ('d');

    EXPECT_CALL (l_engine, quit()).Times(1);
    l_win.keyDown (27);
}

TEST (MapWindow, KAttacksEnemies)
{
    MapWindow       l_win;
    GameEngineMock  l_engine;
    EntityManager   l_entities;
    Event*          l_event = 0;

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    l_win.initialise (&l_engine);

    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_entities.initialise (&l_engine);
    l_entities.createPlayerPrefab (1, 1);

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillRepeatedly (Return (&l_entities));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1).WillOnce(SaveArg<0>(&l_event));
    EXPECT_CALL (l_engine, swapTurn()).Times(1);
    l_win.keyDown ('k');
    l_win.keyDown ('a');
    ASSERT_NE (static_cast<Event*>(0), l_event);
    EXPECT_EQ (EVENT_ATTACK_ENTITY, l_event->getType());

}
