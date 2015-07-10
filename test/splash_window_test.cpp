#include "splash_window.h"
#include "graphics_mock.h"
#include "game_engine_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST (SplashWindow, redraw)
{
    GameEngineMock  l_engine;
    SplashWindow    l_win;
    GraphicsMock    l_graphics;

    EXPECT_CALL (l_engine, getGraphics()).WillRepeatedly (::testing::Return (&l_graphics));
    EXPECT_CALL (l_graphics, drawTile(_, _, _, _, _)).Times (AnyNumber());
    EXPECT_CALL (l_graphics, drawString(_, _, _)).Times (1);

    l_win.initialise (&l_engine);
    l_win.redraw();
}

TEST (SplashWindow, SpaceBarPressed)
{
    GameEngineMock  l_engine;
    SplashWindow    l_win;
    GraphicsMock    l_graphics;

    EXPECT_CALL (l_engine, getGraphics()).WillRepeatedly (::testing::Return (&l_graphics));
    EXPECT_CALL (l_graphics, drawTile(_, _, _, _, _)).Times (AnyNumber());
    EXPECT_CALL (l_graphics, drawString(_, _, _)).Times (1);

    l_win.initialise (&l_engine);

    //l_win.keyDown (' ');
    l_win.redraw();

}
