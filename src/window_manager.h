#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include "window_manager_interface.h"
#include "window_interface.h"
#include <vector>

class GameEngineInterface;

class WindowManager : public WindowManagerInterface {
public:
    void initialise (GameEngineInterface* engine);
    void pushWindow (WindowInterface* win);
    void popWindow ();
    void replaceWindow (WindowInterface* win) ;
    WindowInterface* getActive();
    void redraw ();

private:
    GameEngineInterface*            m_engine;
    std::vector<WindowInterface*>   m_windows;
};

#endif
