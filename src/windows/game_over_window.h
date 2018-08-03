#pragma once

#include "window.h"

typedef struct {
    bool win;
} GameOverWindowArgs;

class GameOverWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void setArguments(std::shared_ptr<GameOverWindowArgs>& args) {
        m_arguments = args;
    }

private:
    std::shared_ptr<GameOverWindowArgs> m_arguments;
};
