#pragma once

#include "window.h"
#include <ctime>

class Camera;

class MapWindow : public Window {
public:
    MapWindow() {}
    ~MapWindow() {}

    void setup() override;
    void registerWidgets() override;

    void nextTurn() override;
    void keyPress(unsigned char key) override;
    void setAction(char action, unsigned int yPos);

private:
    unsigned int m_sidebarWidth = 0;
    unsigned int m_messagesHeight = 0;

    int m_mapStartX = 0;
    int m_mapStartY = 0;

    char m_action = 0;
};
