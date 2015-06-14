#include "window_manager.h"
#include "splash_window.h"

void WindowManager::initialise (GameEngineInterface* engine) {
    m_engine = engine;
    
    Window* l_window = new SplashWindow();
    l_window->initialise();
    addWindow (l_window);
}

void WindowManager::popWindow () {
    Window* win = m_windows.back();
    delete win;
    m_windows.pop_back();
}

void WindowManager::replaceWindow (Window* win) {
    int size = m_windows.size();
    for (int ii = 0; ii < size; ii++) {
        popWindow();
    }
    addWindow (win);
}
