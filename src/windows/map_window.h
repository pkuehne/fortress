#ifndef __MAP_WINDOW_H__
#define __MAP_WINDOW_H__

#include "window.h"
#include <ctime>

class Camera;

class MapWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();

    virtual void nextTurn();
    virtual void keyPress(unsigned char key);
    void setAction(char action, unsigned int yPos);

private:
    unsigned int m_sidebarWidth;
    unsigned int m_messagesHeight;

    int m_mapStartX;
    int m_mapStartY;

    char m_action;
};

#endif
