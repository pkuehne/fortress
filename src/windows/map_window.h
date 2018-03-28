#ifndef __MAP_WINDOW_H__
#define __MAP_WINDOW_H__

#include "window.h"
#include <ctime>

class Camera;

class MapWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();
    
    virtual void redraw();
    virtual void keyPress (unsigned char key);
    void setAction(char action, unsigned int yPos);

private:
    void drawMap ();
    void drawSeparators();
    void drawMessages();
    void drawSidebar();

private:
    unsigned int m_mapXOffset;
    unsigned int m_mapYOffset;
    unsigned int m_mapWidth;
    unsigned int m_mapHeight;

    unsigned int m_sidebarXOffset;
    unsigned int m_sidebarWidth;

    int m_mapStartX;
    int m_mapStartY;

    char    m_action;
    clock_t m_lastDraw;

    bool m_debugMode;
    Camera* m_camera;
};

#endif
