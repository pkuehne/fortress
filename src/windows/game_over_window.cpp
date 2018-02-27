#include "game_over_window.h"
#include "../core/game_engine.h"

void GameOverWindow::registerWidgets()
{
    auto l = createWidget<Label>("lblResult", 2, 2);
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) {
        l->setText("You Win!");
    } else {
        l->setText("You Lose!");
    }
}

void GameOverWindow::setup()
{
    setTitle ("GAME OVER");
    setDimensions (0, 0, 13, 5);
}

void GameOverWindow::keyDown (unsigned char key)
{
    if (key == KEY_ESC) getEngine()->quit();
}
