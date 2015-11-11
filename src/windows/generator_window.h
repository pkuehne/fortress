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

enum GenerationStatus {
	WAITING = 0,
	PROGRESS,
	COMPLETED,
	ABORTED,
	MAX
};

class GeneratorWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void update();
    virtual void keyDown (unsigned char key);

private:
    std::string formatNumber (int number);
    void startGenerating ();
    void generateLevel();
    void startPlaying();

private:
    PositionSelect m_selectedPosition;
    unsigned int m_levelWidth;
    unsigned int m_levelHeight;
    unsigned int m_levelRooms;
    unsigned int m_worldSize;
    unsigned int m_levelDepth;

    GenerationStatus	m_status;
    unsigned int m_progress = 0;
};

#endif
