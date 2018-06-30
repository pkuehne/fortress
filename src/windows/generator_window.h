#ifndef GENERATOR_WINDOW
#define GENERATOR_WINDOW

#include "../generators/generator_interface.h"
#include "window.h"

enum PositionSelect { NONE = 0, WIDTH, HEIGHT, ROOMS, DEPTH };

enum GenerationStatus { WAITING = 0, PROGRESS, COMPLETED, ABORTED, MAX };

typedef struct {
    bool hideWindow;
} GeneratorWindowArgs;

class GeneratorWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();

    virtual void redraw();

    void setArguments(std::shared_ptr<GeneratorWindowArgs>& args) {
        m_arguments = args;
    }

private:
    void startGenerating();
    void generateLevel();
    void startPlaying();

private:
    PositionSelect m_selectedPosition;
    unsigned int m_worldSize;

    GenerationStatus m_status;
    unsigned int m_progress = 0;

    std::shared_ptr<GeneratorWindowArgs> m_arguments;
};

#endif
