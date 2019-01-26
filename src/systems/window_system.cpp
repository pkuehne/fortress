#include "window_system.h"
#include "../windows/map_window.h"

void WindowSystem::registerHandlers() {
    events()->subscribe<CreateMapWindowEvent>(
        [=](std::shared_ptr<CreateMapWindowEvent> event) {
            auto l_win = std::make_shared<MapWindow>();
            l_win->initialise(getEngine());
            getEngine()->getWindows()->replaceAllWindows(l_win);
        });
}