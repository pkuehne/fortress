#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include "window_manager_interface.h"
#include "window.h"
#include <vector>

class GameEngineInterface;

class WindowManager : public WindowManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void addWindow (Window* win) { m_windows.push_back (win); }
    void popWindow ();
    void replaceWindow (Window* win) ;
    Window* getActive() { return m_windows.back(); }

private:
    GameEngineInterface*    m_engine;
    std::vector<Window*>    m_windows;
};

#endif
