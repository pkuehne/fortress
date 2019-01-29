#include "window_system.h"
#include "../windows/map_window.h"

void WindowSystem::registerHandlers() {
    events()->subscribe<RegisterWindowEvent>(
        [=](std::shared_ptr<RegisterWindowEvent> event) {
            event->window->initialise(getEngine());
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
        });
}