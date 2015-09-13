#ifndef GENERATOR_WINDOW
#define GENERATOR_WINDOW

#include "window.h"

enum PositionSelect {
    NONE = 0,
    WIDTH,
    HEIGHT,
    ROOMS,
};

class GeneratorWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    std::string formatNumber (int number);

private:
    PositionSelect m_selectedPosition;
    unsigned int m_levelWidth;
    unsigned int m_levelHeight;
    unsigned int m_levelRooms;
    unsigned int m_worldSize;
};

#endif
