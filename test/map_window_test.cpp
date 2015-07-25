#include "map_window.h"
#include "game_engine_mock.h"
#include "entity_manager_mock.h"
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
    ComponentManager<SpriteComponent>   l_component;
    Entity              l_entity;
    SpriteComponent     l_sprite;
    l_sprite.yPos   = 1;
    l_sprite.xPos   = 1;
    l_sprite.sprite = 180;
    l_component.add (&l_entity, l_sprite);

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_engine, getGraphics()).Times(1).WillRepeatedly (Return (&l_graphics));
    EXPECT_CALL (l_entities, getSprites()).Times(1).WillOnce (Return (&l_component));
    EXPECT_CALL (l_graphics, drawTile(Eq(l_sprite.yPos), Eq(l_sprite.xPos), Eq(l_sprite.sprite), _, _)).Times(1);
    l_win.initialise (&l_engine);
    l_win.redraw();
    //FAIL() << "Not finished";
}

TEST (MapWindow, WASDMovesPlayer)
{
    MapWindow       l_win;
    GameEngineMock  l_engine;
    EntityManagerMock   l_entities;
    Entity          l_entity;
    MoveEntityEvent* l_event = new MoveEntityEvent;

    l_event->entity     = l_entity.getId();

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    EXPECT_CALL (l_engine, swapTurn()).Times(5);
    l_win.initialise (&l_engine);

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (&l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::North;
    l_win.keyDown ('w');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (&l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::South;
    l_win.keyDown ('s');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (&l_entity));
    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1);
    l_event->direction  = Direction::West;
    l_win.keyDown ('a');

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_entities, getPlayer()).WillOnce (Return (&l_entity));
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
    EntityManagerMock   l_entities;
    Event*          l_event = 0;
    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    l_win.initialise (&l_engine);

    EXPECT_CALL (l_engine, raiseEvent (_)).Times(1).WillOnce(SaveArg<0>(&l_event));
    EXPECT_CALL (l_engine, swapTurn()).Times(1);
    l_win.keyDown ('k');
    ASSERT_NE (static_cast<Event*>(0), l_event);
    EXPECT_EQ (EVENT_ATTACK_ENTITY, l_event->getType());

}
