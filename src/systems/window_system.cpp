#include "window_system.h"
#include "../windows/map_window.h"

void WindowSystem::registerHandlers() {
    auto registerHandler = [=](std::shared_ptr<RegisterWindowEvent> event) {
        event->window->initialise(getEngine(), events(), components(),
                                  entities(), map());

        auto manager = getEngine()->getWindows();
        switch (event->action) {
            case RegisterWindowEvent::WindowAction::Add:
                manager->pushWindow(event->window);
                break;
            case RegisterWindowEvent::WindowAction::Replace:
                manager->popWindow();
                manager->pushWindow(event->window);
                break;
            case RegisterWindowEvent::WindowAction::ReplaceAll:
                manager->popAllWindows();
                manager->pushWindow(event->window);
            default:
                break;
        }
    };
    auto closeHandler = [&](std::shared_ptr<CloseWindowEvent> event) {
        getEngine()->getWindows()->popWindow();
    };
    auto resizeHandler = [&](std::shared_ptr<ResizeWindowsEvent> event) {
        getEngine()->getWindows()->resize();
    };

    events()->subscribe<RegisterWindowEvent>(registerHandler);
    events()->subscribe<CloseWindowEvent>(closeHandler);
    events()->subscribe<ResizeWindowsEvent>(resizeHandler);
}