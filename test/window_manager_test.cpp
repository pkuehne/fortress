#include "window_manager.h"
#include "game_engine_mock.h"
#include "splash_window.h"
#include "window_mock.h"

#include <gtest/gtest.h>

TEST (WindowManager, initialise)
{
    GameEngineMock  l_engine;
    WindowManager   l_manager;

    l_manager.initialise (&l_engine);
    EXPECT_NE (static_cast<SplashWindow*>(0), l_manager.getActive());
}

TEST (WindowManager, ReplaceAndPop)
{
    GameEngineMock  l_engine;
    WindowManager   l_manager;
    WindowMock*     l_win = new WindowMock();

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
