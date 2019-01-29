#include "window_manager.h"
#include "../windows/splash_window.h"
#include "game_engine.h"
#include <cassert>
#include <glog/logging.h>

void WindowManager::removeWindow(std::shared_ptr<Window> win) {
    win->destroy();
}

void WindowManager::initialise(GameEngine* engine) { m_engine = engine; }

void WindowManager::pushWindow(std::shared_ptr<Window> win) {
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

void WindowManager::popAllWindows() {
    for (auto win : m_windows) {
        removeWindow(win);
    }
    m_windows.clear();
}

std::shared_ptr<Window> WindowManager::getActive() {
    if (m_windows.size() == 0) {
        throw std::string("There are no active windows!");
    }
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
