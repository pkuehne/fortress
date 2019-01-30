#pragma once

#include "../generators/generator_interface.h"
#include "window.h"

enum PositionSelect { NONE = 0, WIDTH, HEIGHT, ROOMS, DEPTH };

enum GenerationStatus { WAITING = 0, PROGRESS, COMPLETED, ABORTED, MAX };

typedef struct {
    bool hideWindow;
} GeneratorWindowArgs;

class GeneratorWindow : public Window {
public:
    explicit GeneratorWindow(bool hideWindow) : m_hideWindow(hideWindow) {}
    virtual void setup();
    virtual void registerWidgets();

    virtual void redraw();

    void setArguments(std::shared_ptr<GeneratorWindowArgs>& args) {
        m_arguments = args;
    }

private:
    void generateGroupings();
    void startGenerating();
    void startPlaying();

private:
    PositionSelect m_selectedPosition = PositionSelect::NONE;
    unsigned int m_worldSize = 0;

    GenerationStatus m_status = GenerationStatus::WAITING;
    unsigned int m_progress = 0;

    std::shared_ptr<GeneratorWindowArgs> m_arguments;
    bool m_hideWindow;
};
