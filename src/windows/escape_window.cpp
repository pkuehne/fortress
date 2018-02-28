#include "escape_window.h"
#include "../core/game_engine.h"

void quit(Label *l)
{
    l->getWindow()->getEngine()->quit();
}

void EscapeWindow::registerWidgets()
{
    setTitle(" FORTRESS ");
    setFullscreen(true);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);

    this->createWidget<Label>("lblEsc", 0, 2)
        ->setText("Press ESC to return")
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblSaveGame", 0, 3)
        ->setText("Save Game")
        ->setCommandChar(1)
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblReload", 0, 4)
        ->setText("Reload Config")
        ->setCommandChar(1)
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblQuit", 0, 5)
        ->setText("Quit Game")
        ->setCommandChar(1)
        ->setCommandCharCallback(quit)
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
    this->createWidget<Label>("lblQuit2", 0, 0)
        ->setText("quit")
        ->setCommandChar(1)
        ->setCommandCharCallback(quit)
        ->setVisible(false);
}