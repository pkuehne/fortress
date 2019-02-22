#include "window_manager.h"
#include "../windows/window.h"
#include "event.h"
#include "game_engine.h"
#include <glog/logging.h>

void WindowManager::registerHandlers() {
    auto registerHandler = [this](std::shared_ptr<RegisterWindowEvent> event) {
        event->window->initialise(this->m_engine, events(), components(),
                                  entities(), map());

        switch (event->action) {
            case RegisterWindowEvent::WindowAction::Add:
                this->pushWindow(event->window);
                break;
            case RegisterWindowEvent::WindowAction::Replace:
                this->popWindow();
                this->pushWindow(event->window);
                break;
            case RegisterWindowEvent::WindowAction::ReplaceAll:
                this->popAllWindows();
                this->pushWindow(event->window);
            default:
                break;
        }
    };
    auto closeHandler = [this](std::shared_ptr<CloseWindowEvent> event) {
        popWindow();
    };
    auto resizeHandler = [this](std::shared_ptr<ResizeWindowsEvent> event) {
        this->resize();
    };

    events()->subscribe<RegisterWindowEvent>(registerHandler);
    events()->subscribe<CloseWindowEvent>(closeHandler);
    events()->subscribe<ResizeWindowsEvent>(resizeHandler);
}

void WindowManager::removeWindow(std::shared_ptr<Window> win) {
    win->destroy();
}

void WindowManager::initialise(GameEngine* engine,
                               std::shared_ptr<GraphicsInterface> graphics,
                               std::shared_ptr<EventManager> events,
                               std::shared_ptr<ComponentManager> components,
                               std::shared_ptr<EntityManager> entities,
                               std::shared_ptr<MapManager> map) {
    m_engine = engine;
    m_graphics = graphics;
    m_events = events;
    m_components = components;
    m_entities = entities;
    m_map = map;
}

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
