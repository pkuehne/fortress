#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include "window.h"
#include "game_engine_interface.h"
#include <vector>

class WindowManager {
public:
    void initialise (GameEngineInterface* engine);
    void addWindow (Window* win) { m_windows.push_back (win); }
    void popWindow ();
    void replaceWindow (Window* win) ;
    Window* getWindow() { return m_windows.back(); }

private:
    GameEngineInterface*    m_engine;
    std::vector<Window*>    m_windows;
};

#endif
