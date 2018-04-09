#include "game_engine.h"
#include "window_manager.h"
#include "../windows/splash_window.h"
#include <cassert>

void removeWindow(Window *win)
{
    win->loseFocus();
    delete win;
}

void WindowManager::initialise(GameEngine *engine)
{
    m_engine = engine;

    createWindow<SplashWindow>();
}

void WindowManager::pushWindow(Window *win)
{
    m_windows.push_back(win);

    win->gainFocus(); // TODO: Remove when MapWindow is migrated
    win->setup();
    win->registerWidgets();
    win->resize();
}

void WindowManager::popWindow()
{
    if (!m_windows.size())
    {
        return;
    }
    removeWindow(m_windows.back());
    m_windows.pop_back();
}

void WindowManager::replaceWindow(Window *win)
{
    popWindow();
    pushWindow(win);
}

void WindowManager::replaceAllWindows(Window *win)
{
    m_nextWindow = win;
    m_nextAction = NextWindowAction::ReplaceAll;
}

Window *WindowManager::getActive()
{
    if (m_windows.size() == 0)
        return NULL;
    return m_windows.back();
}

void WindowManager::nextTick()
{
    m_engine->getGraphics()->beginScreenUpdate();

    for (size_t ii = 0; ii < m_windows.size(); ii++)
    {
        m_windows[ii]->beforeRedraw();
        m_windows[ii]->redraw();
        m_windows[ii]->renderWidgets();
        m_windows[ii]->afterRedraw();
    }
    m_engine->getGraphics()->endScreenUpdate();
    
    manageNextWindow();
}

void WindowManager::resize()
{
    for (size_t ii = 0; ii < m_windows.size(); ii++)
    {
        m_windows[ii]->resize();
    }
}

void WindowManager::nextTurn()
{
    for (size_t ii = 0; ii < m_windows.size(); ii++)
    {
        m_windows[ii]->nextTurn();
    }
}

void WindowManager::manageNextWindow()
{
    if (!m_nextWindow)
    {
        return;
    }

    switch (m_nextAction)
    {
    case NextWindowAction::Replace:
    {
        popWindow();
        pushWindow(m_nextWindow);
        break;
    }
    case NextWindowAction::ReplaceAll:
    {
        for (Window* win : m_windows)
        {
            removeWindow(win);
        }
        m_windows.clear();

        pushWindow(m_nextWindow);
        break;
    }
    }
    m_nextWindow = nullptr;
}