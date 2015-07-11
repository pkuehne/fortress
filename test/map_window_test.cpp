#include "map_window.h"
#include "game_engine_mock.h"
#include "entity_manager_mock.h"
#include "component_manager_mock.h"
#include "graphics_mock.h"
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
    l_component.add (&l_entity, l_sprite);

    EXPECT_CALL (l_engine, loadMap (StrEq(""))).Times(1);
    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    EXPECT_CALL (l_engine, getGraphics()).Times(1).WillRepeatedly (Return (&l_graphics));
    EXPECT_CALL (l_entities, getSprites()).Times(1).WillOnce (Return (&l_component));
    EXPECT_CALL (l_graphics, drawTile(Eq(1), Eq(0), Eq(0), _, _)).Times(1);
    l_win.initialise (&l_engine);
    l_win.redraw();
    //FAIL() << "Not finished";
}

TEST (MapWindow, keyDownMovesPlayer)
{
    FAIL() << "Not finished";
}
