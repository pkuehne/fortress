#include "game_over_window.h"
#include "gameengine.h"

void GameOverWindow::gainFocus() {
    getEngine()->getGraphics()->clearArea (10, 20, 5, 11);
    getEngine()->getGraphics()->drawBorder (10, 20, 5, 11);

    getEngine()->getGraphics()->drawString (12, 22, "GAME OVER");
    getEngine()->getGraphics()->drawString (14, 22, "You lose!");

}
