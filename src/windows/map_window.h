#ifndef __MAP_WINDOW_H__
#define __MAP_WINDOW_H__

#include "window.h"
#include <ctime>

class Camera;

class MapWindow : public Window {
public:
    MapWindow() {}
    ~MapWindow() {}

    virtual void setup();
    virtual void registerWidgets();

    virtual void nextTurn();
    virtual void keyPress(unsigned char key);
    void setAction(char action, unsigned int yPos);

private:
    unsigned int m_sidebarWidth = 0;
    unsigned int m_messagesHeight = 0;

    int m_mapStartX = 0;
    int m_mapStartY = 0;

    char m_action = 0;
};

#endif
