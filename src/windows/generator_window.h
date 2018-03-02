#ifndef GENERATOR_WINDOW
#define GENERATOR_WINDOW

#include "window.h"
#include "../generators/generator_interface.h"

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

    virtual void setup();
    virtual void registerWidgets();

    virtual void update();

private:
    void startGenerating ();
    void generateLevel();
    void startPlaying();

private:
    PositionSelect m_selectedPosition;
    unsigned int m_worldSize;

    GenerationStatus	m_status;
    unsigned int m_progress = 0;
};

#endif
