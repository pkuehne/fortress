#include "escape_window.h"
#include "../core/game_engine.h"
#include "label.h"

void EscapeWindow::setup() {
    setTitle(" FORTRESS ");
    setFullscreen();
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void EscapeWindow::registerWidgets() {
    this->createWidget<Label>("lblEsc", 0, 1)
        ->setText("Press ESC to return")
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblSaveGame", 0, 3)
        ->setText("Save Game")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            l->getWindow()->getEngine()->state()->save("test.yaml");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblReload", 0, 4)
        ->setText("Reload Config")
        ->setCommandChar(1)
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre)
        ->setSensitive(false);
    this->createWidget<Label>("lblQuit", 0, 5)
        ->setText("Quit Game")
        ->setCommandChar(1)
        ->setCommandCharCallback(
            [](Label* l) { l->getWindow()->getEngine()->quit(); })
        ->setIgnoreCommandCharCase(true)
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
}