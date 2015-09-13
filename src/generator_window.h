#ifndef GENERATOR_WINDOW
#define GENERATOR_WINDOW

#include "window.h"

class GeneratorWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    unsigned int m_levelWidth;
    unsigned int m_levelHeight;
    unsigned int m_levelRooms;
    unsigned int m_worldSize;
};

#endif
