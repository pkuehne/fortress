#include "main_window.h"
#include "map_window.h"
#include "generator_window.h"
#include "label.h"
#include "../core/game_engine.h"

void MainWindow::setup()
{
    setTitle(" FORTRESS ");
    setFullscreen(true);
    setEscapeBehaviour(Window::EscapeBehaviour::QuitGame);
}
void MainWindow::registerWidgets()
{
    Label::CommandCharCB quickstart = [](Label *l) {
        l->getWindow()->getEngine()->getWindows()->createWindow<GeneratorWindow>((void *)1);
    };
    Label::CommandCharCB create = [](Label *l) {
        l->getWindow()->getEngine()->getWindows()->createWindow<GeneratorWindow>();
    };

    this->createWidget<Label>("lblQuickstart", 1, 15)
        ->setText("Quickstart")
        ->setCommandChar(1)
        ->setCommandCharCallback(quickstart)
        ->setIgnoreCommandCharCase(true)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);

    this->createWidget<Label>("lblCreate", 1, 12)
        ->setText("Create New World")
        ->setCommandChar(1)
        ->setCommandCharCallback(create)
        ->setIgnoreCommandCharCase(true)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);

    this->createWidget<Label>("lblLoad", 1, 9)
        ->setText("Load Existing World")
        ->setCommandChar(1)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);

    this->createWidget<Label>("lblTutorial", 1, 6)
        ->setText("Start The Tutorial")
        ->setCommandChar(1)
        ->setSensitive(false)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
}
