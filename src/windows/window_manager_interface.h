#ifndef WINDOW_MANAGER_INTERFACE_H
#define WINDOW_MANAGER_INTERFACE_H

#include "window_interface.h"
#include "game_engine_interface.h"

class WindowManagerInterface {
public:
    virtual ~WindowManagerInterface() { }
    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void pushWindow (WindowInterface* win) = 0;
    virtual void popWindow () = 0;
    virtual void replaceWindow (WindowInterface* win) = 0;
    virtual void replaceAllWindows (WindowInterface* win) = 0;
    virtual WindowInterface* getActive() = 0;
    virtual void redraw() = 0;
    virtual void resize () = 0;
    virtual void update () = 0;
};

#endif
