#ifndef GAME_OVER_WINDOW_H
#define GAME_OVER_WINDOW_H

#include "window.h"

class GameOverWindow : public Window {
public:
    void gainFocus();
    void redraw();
};

#endif
