#ifndef __MAP_WINDOW_H__
#define __MAP_WINDOW_H__

#include "window.h"

class MapWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    void drawMap ();

private:
    int m_mapXOffset;
    int m_mapYOffset;
};

#endif
