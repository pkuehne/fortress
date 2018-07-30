#include "dialog_window.h"
#include "../core/game_engine.h"
#include "label.h"

void DialogWindow::setup() {
    setTitle("Dialog");
    setHeight(15);
    setWidth(40);

    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void DialogWindow::registerWidgets() {
    createWidget<Label>("lblResponse", 0, 0)->setText("Response...");
}
