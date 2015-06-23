#ifndef __MAP_WINDOW_H__
#define __MAP_WINDOW_H__

#include "window.h"

class MapWindow : public Window {
public:
    virtual void initialise();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    void drawMap ();
};

#endif
