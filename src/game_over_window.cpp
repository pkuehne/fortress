#include "game_over_window.h"
#include "gameengine.h"

void GameOverWindow::gainFocus()
{
    setTitle ("GAME OVER");
}

void GameOverWindow::redraw()
{
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) {
        drawString (2, 2, "You Win!");
    } else {
        drawString (2, 2, "You Lose!");
    }
}

void GameOverWindow::resize()
{
    setDimensions (0, 0, 13, 5);
}

void GameOverWindow::keyDown (unsigned char key)
{
    if (key == 27) getEngine()->quit();
}
