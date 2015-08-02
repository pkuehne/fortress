#include "game_over_window.h"
#include "gameengine.h"

void GameOverWindow::redraw()
{
    drawString (2, 2, "GAME OVER");
    drawString (3, 2, "You lose!");
}

void GameOverWindow::gainFocus()
{
    setDimensions (0, 0, 13, 6);
}
