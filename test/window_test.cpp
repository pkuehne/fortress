#include "window.h"
#include <gtest/gtest.h>
#include "graphics_mock.h"
#include "game_engine_mock.h"

using namespace ::testing;

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
//    GameEngineMock* m_engine = new GameEngineMock();

    Window l_win;
//    l_win.initialise (m_engine);

    EXPECT_FALSE (l_win.getKey('A'));
    l_win.keyDown ('A');
    EXPECT_TRUE (l_win.getKey('A'));
    l_win.keyUp ('A');
    EXPECT_FALSE (l_win.getKey('A'));
}

TEST (Window, Redraw)
{
    GameEngineMock* m_engine    = new GameEngineMock();
    GraphicsMock*   m_graphics  = new GraphicsMock();
    Window l_win;

    EXPECT_CALL (*m_engine, getGraphics())
        .Times(2)
        .WillRepeatedly (Return(m_graphics));
    EXPECT_CALL (*m_graphics, beginScreenUpdate())
        .Times (1);
    EXPECT_CALL (*m_graphics, endScreenUpdate())
        .Times (1);

    l_win.initialise (m_engine);

    l_win.beforeRedraw();
    l_win.redraw();
    l_win.afterRedraw();

    delete m_engine;
    delete m_graphics;
}

TEST (Window, MouseButtons)
{
    Window l_win;

    EXPECT_FALSE (l_win.getMouseButton (1));
    l_win.mouseDown (0, 0, 1);
    EXPECT_TRUE (l_win.getMouseButton (1));
    l_win.mouseUp (0, 0, 1);
    EXPECT_FALSE (l_win.getMouseButton (1));
}

TEST (Window, MouseButtonsHaveAMax)
{
    Window l_win;

    EXPECT_FALSE (l_win.getMouseButton (Window::MAX_BUTTONS));
    l_win.mouseDown (0, 0, 1);
    EXPECT_FALSE (l_win.getMouseButton (Window::MAX_BUTTONS));
    l_win.mouseUp (0, 0, 1);
    EXPECT_FALSE (l_win.getMouseButton (Window::MAX_BUTTONS));
}

TEST (Window, Resize)
{
    Window l_win;

    EXPECT_NO_THROW (l_win.resize (0, 0));
}
