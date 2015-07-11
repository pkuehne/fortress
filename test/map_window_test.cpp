#include "map_window.h"
#include "game_engine_mock.h"
#include "entity_manager_mock.h"
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

    EXPECT_CALL (l_engine, getEntities()).Times(1).WillOnce(Return (&l_entities));
    l_win.initialise (&l_engine);
    l_win.redraw();
    //FAIL() << "Not finished";
}

TEST (MapWindow, keyDownMovesPlayer)
{
    FAIL() << "Not finished";
}
