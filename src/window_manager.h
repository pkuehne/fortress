#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include "window.h"
#include <vector>

class WindowManager {
public:
    void initialise();
    void addWindow (Window* win) { m_windows.push_back (win); }
    void popWindow ();
    void replaceWindow (Window* win) ;
    Window* getWindow() { return m_windows.back(); }

private:
    std::vector<Window*>    m_windows;
};

#endif
