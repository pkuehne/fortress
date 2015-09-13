#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "main_window.h"
#include "map_window.h"
#include "gameengine.h"

class MainWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:

};

#endif
