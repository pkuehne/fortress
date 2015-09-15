#ifndef GENERATOR_WINDOW
#define GENERATOR_WINDOW

#include "window.h"
#include "generator_interface.h"

enum PositionSelect {
    NONE = 0,
    WIDTH,
    HEIGHT,
    ROOMS,
    DEPTH
};

class GeneratorWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    std::string formatNumber (int number);
    void startGenerating ();
    void startPlaying();

private:
    PositionSelect m_selectedPosition;
    unsigned int m_levelWidth;
    unsigned int m_levelHeight;
    unsigned int m_levelRooms;
    unsigned int m_worldSize;
    unsigned int m_levelDepth;

    GeneratorInterface* m_generator;
    bool                m_generating;
    bool                m_generated;
    unsigned int        m_generatingLevel;
};

#endif
