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
    void drawSeparators();
    void drawMessages();
    void drawSidebar();
    void drawProgressBar (int x, int y, int value);

private:
    unsigned int m_mapXOffset;
    unsigned int m_mapYOffset;
    unsigned int m_mapWidth;
    unsigned int m_mapHeight;

    unsigned int m_sidebarXOffset;
    unsigned int m_sidebarWidth;

    int m_mapStartX;
    int m_mapStartY;

    char m_action;
};

#endif
