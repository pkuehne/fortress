#include "game_over_window.h"
#include "../core/event_manager.h"
#include "../widgets/label.h"

void GameOverWindow::registerWidgets() {
    Label* l = createWidget<Label>("lblResult", 2, 2);
    if (m_win) {
        l->setText("You Win!");
    } else {
        l->setText("You Lose!");
    }
}

void GameOverWindow::setup() {
    setTitle("GAME OVER");
    setHeight(5);
    setWidth(13);

    setEscapeBehaviour(Window::EscapeBehaviour::QuitGame);
}
