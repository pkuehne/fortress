#include "window_manager.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../core/event_manager.h"
#include "../core/map_manager.h"
#include "../core/window_manager.h"
#include "../windows/window.h"
#include "event.h"
#include <spdlog/spdlog.h>

void WindowManager::registerHandlers() {
    auto registerHandler = [this](const RegisterWindowEvent& event) {
        event.window->initialise(graphics(), events(), entities(), map());

        switch (event.action) {
            case RegisterWindowEvent::WindowAction::Add:
                this->pushWindow(std::move(event.window));
                break;
            case RegisterWindowEvent::WindowAction::Replace:
                this->popWindow();
                this->pushWindow(std::move(event.window));
                break;
            case RegisterWindowEvent::WindowAction::ReplaceAll:
                this->popAllWindows();
                this->pushWindow(std::move(event.window));
            default:
                break;
        }
    };
    auto closeHandler = [this](const CloseWindowEvent& event) { popWindow(); };
    auto resizeHandler = [this](const ResizeWindowsEvent& event) {
        this->resize();
    };

    events()->subscribe<RegisterWindowEvent>(registerHandler);
    events()->subscribe<CloseWindowEvent>(closeHandler);
    events()->subscribe<ResizeWindowsEvent>(resizeHandler);
}

void WindowManager::removeWindow(Window& win) { win.destroy(); }

void WindowManager::initialise(std::shared_ptr<GraphicsInterface> graphics,
                               std::shared_ptr<EventManager> events,
                               std::shared_ptr<EntityManager> entities,
                               std::shared_ptr<MapManager> map) {
    m_graphics = graphics;
    m_events = events;
    m_entities = entities;
    m_map = map;
    registerHandlers();
}

void WindowManager::pushWindow(std::unique_ptr<Window> win) {
    win->setup();
    win->registerWidgets();
    win->resize();
    win->nextTurn(); // Force re-fresh on all widgets

    m_windows.push_back(std::move(win));
}

void WindowManager::popWindow() {
    if (!m_windows.size()) {
        return;
    }
    removeWindow(*m_windows.back());
    m_windows.pop_back();
}

void WindowManager::popAllWindows() {
    for (auto& win : m_windows) {
        removeWindow(*win);
    }
    m_windows.clear();
}

Window* WindowManager::getActive() {
    if (m_windows.size() == 0) {
        throw std::string("There are no active windows!");
    }
    return m_windows.back().get();
}

void WindowManager::nextTick() {
    graphics()->beginScreenUpdate();

    for (size_t ii = 0; ii < m_windows.size(); ii++) {
        m_windows[ii]->beforeRedraw();
        m_windows[ii]->redraw();
        m_windows[ii]->renderWidgets();
        m_windows[ii]->afterRedraw();
    }
    graphics()->endScreenUpdate();
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
