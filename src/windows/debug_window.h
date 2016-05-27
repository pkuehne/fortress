#ifndef __DEBUG_WINDOW_H__
#define __DEBUG_WINDOW_H__

#include "window.h"

class DebugWindow : public Window {
public:
    void gainFocus();
    void resize();
    void redraw();
    void keyDown (unsigned char key);
private:
    std::string command;
};

#endif
