#include "window_manager.h"
#include "../windows/splash_window.h"
#include "game_engine.h"
#include <cassert>
#include <glog/logging.h>

void removeWindow(Window* win) {
    win->destroy();
    delete win;
}

void WindowManager::initialise(GameEngine* engine) {
    m_engine = engine;

    createWindow<SplashWindow>();
}

void WindowManager::pushWindow(Window* win) {
    m_windows.push_back(win);

    win->setup();
    win->registerWidgets();
    win->resize();
    win->nextTurn(); // Force re-fresh on all widgets
}

void WindowManager::popWindow() {
    if (!m_windows.size()) {
        return;
    }
    removeWindow(m_windows.back());
    m_windows.pop_back();
}

// void WindowManager::replaceWindow(Window* win) {
//     m_nextWindow = win;
//     m_nextAction = NextWindowAction::Replace;
// }

void WindowManager::replaceAllWindows(Window* win) {
    m_nextWindow = win;
    m_nextAction = NextWindowAction::ReplaceAll;
}

Window* WindowManager::getActive() {
    if (m_windows.size() == 0)
        return NULL;
    return m_windows.back();
}

void WindowManager::nextTick() {
    m_engine->getGraphics()->beginScreenUpdate();

    for (size_t ii = 0; ii < m_windows.size(); ii++) {
        m_windows[ii]->beforeRedraw();
        m_windows[ii]->redraw();
        m_windows[ii]->renderWidgets();
        m_windows[ii]->afterRedraw();
    }
    m_engine->getGraphics()->endScreenUpdate();

    manageNextWindow();
}

void WindowManager::resize() {
    for (size_t ii = 0; ii < m_windows.size(); ii++) {
        m_windows[ii]->resize();
    }
}

void WindowManager::nextTurn() {
    for (size_t ii = 0; ii < m_windows.size(); ii++) {
        m_windows[ii]->nextTurn();
    }
}

void WindowManager::manageNextWindow() {
    if (!m_nextWindow) {
        return;
    }

    switch (m_nextAction) {
        case NextWindowAction::Replace: {
            popWindow();
            pushWindow(m_nextWindow);
            break;
        }
        case NextWindowAction::ReplaceAll: {
            for (Window* win : m_windows) {
                removeWindow(win);
            }
            m_windows.clear();

            pushWindow(m_nextWindow);
            break;
        }
        case NextWindowAction::None:
        default:
            LOG(ERROR) << "Invalid window action for next window" << std::endl;
            break;
    }
    m_nextWindow = nullptr;
    m_nextAction = NextWindowAction::None;
}