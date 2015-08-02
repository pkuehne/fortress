#include "game_over_window.h"
#include "gameengine.h"

void GameOverWindow::gainFocus()
{
    setTitle ("GAME OVER");
}

void GameOverWindow::redraw()
{
    drawString (2, 2, "You lose!");
}

void GameOverWindow::resize()
{
    setDimensions (0, 0, 13, 5);
}
