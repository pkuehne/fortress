#include "escape_window.h"
#include "../core/game_engine.h"

void EscapeWindow::registerWidgets()
{
    setTitle(" FORTRESS ");

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
        ->setVerticalAlign(Widget::VerticalAlign::Top)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
}

void EscapeWindow::resize()
{
    setDimensions(0, 0,
                  getEngine()->getGraphics()->getScreenWidth(),
                  getEngine()->getGraphics()->getScreenHeight());
}

void EscapeWindow::keyDown(unsigned char key)
{
    if (key == KEY_ESC)
    {
        getEngine()->getWindows()->popWindow();
    }
    if (toupper(key) == 'Q')
    {
        getEngine()->quit();
    }
}
