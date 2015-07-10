#include "window.h"
#include <gtest/gtest.h>
#include "graphics_mock.h"
#include "game_engine_mock.h"

TEST (Window, initialise)
{
    GameEngineMock* m_engine = new GameEngineMock();

    Window l_win;

    EXPECT_EQ (static_cast<GameEngineInterface*>(0), l_win.getEngine());
    l_win.initialise (m_engine);
    EXPECT_EQ (m_engine, l_win.getEngine());
    l_win.destroy();
    EXPECT_EQ (m_engine, l_win.getEngine()); // Since the destroy does nothing
}

TEST (Window, keyDownGetAndUp)
{
    GameEngineMock* m_engine = new GameEngineMock();

    Window l_win;
    l_win.initialise (m_engine);

    EXPECT_FALSE (l_win.getKey('A'));
    l_win.keyDown ('A');
    EXPECT_TRUE (l_win.getKey('A'));
    l_win.keyUp ('A');
    EXPECT_FALSE (l_win.getKey('A'));
}
