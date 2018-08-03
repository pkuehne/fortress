#include "main_window.h"
#include "../core/file_loader.h"
#include "../core/game_engine.h"
#include "../widgets/label.h"
#include "generator_window.h"
#include "load_window.h"

void MainWindow::setup() {
    setTitle("FORTRESS");
    setFullscreen();
    setEscapeBehaviour(Window::EscapeBehaviour::QuitGame);
}
void MainWindow::registerWidgets() {
    Label::CommandCharCB quickstart = [=](Label* l) {
        auto args = std::make_shared<GeneratorWindowArgs>();
        args->hideWindow = true;
        auto win = std::make_shared<GeneratorWindow>();
        win->setArguments(args);
        getEngine()->getWindows()->registerWindow(win);
    };
    Label::CommandCharCB create = [](Label* l) {
        auto args = std::make_shared<GeneratorWindowArgs>();
        args->hideWindow = false;
        auto win = std::make_shared<GeneratorWindow>();
        win->setArguments(args);
        l->getWindow()->getEngine()->getWindows()->registerWindow(win);
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
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([=](Label* l) {
            getEngine()->getWindows()->registerWindow(
                std::make_shared<LoadWindow>());
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);

    this->createWidget<Label>("lblTutorial", 1, 6)
        ->setText("Start The Tutorial")
        ->setCommandChar(1)
        ->setSensitive(false)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre);
}
