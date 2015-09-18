#include "window_manager.h"
#include "game_engine_mock.h"
#include "graphics_mock.h"
#include "splash_window.h"
#include "window_mock.h"

#include <gtest/gtest.h>

using namespace ::testing;

TEST (WindowManager, initialise)
{
    GameEngineMock  l_engine;
    GraphicsMock    l_graphics;
    WindowManager   l_manager;

    EXPECT_CALL (l_engine, getGraphics()).WillRepeatedly (Return (&l_graphics));
    EXPECT_CALL (l_graphics, calculateWindowOffsetsFromCentre(_,_,_,_)).Times (2);
    l_manager.initialise (&l_engine);
    EXPECT_NE (static_cast<SplashWindow*>(0), l_manager.getActive());
}

TEST (WindowManager, ReplaceAndPop)
{
    GameEngineMock  l_engine;
    GraphicsMock    l_graphics;
    WindowManager   l_manager;
    WindowMock*     l_win = new WindowMock();

    EXPECT_CALL (l_engine, getGraphics()).WillRepeatedly (Return (&l_graphics));
    EXPECT_CALL (l_graphics, calculateWindowOffsetsFromCentre(_,_,_,_)).Times (2);
    EXPECT_CALL (*l_win, gainFocus()).Times(1);
    EXPECT_CALL (*l_win, loseFocus()).Times(1);
    EXPECT_CALL (*l_win, resize()).Times(1);

    l_manager.initialise (&l_engine);
    EXPECT_NE (static_cast<SplashWindow*>(0), l_manager.getActive());
    l_manager.replaceWindow (l_win);
    EXPECT_EQ (l_win, l_manager.getActive());
    l_manager.popWindow();
    EXPECT_EQ (static_cast<WindowInterface*>(0), l_manager.getActive());
}

TEST (WindowManager, PopEmptyStack)
{
    WindowManager   l_manager;

    EXPECT_EQ (static_cast<WindowInterface*>(0), l_manager.getActive());
    l_manager.popWindow();
    EXPECT_EQ (static_cast<WindowInterface*>(0), l_manager.getActive());
}
