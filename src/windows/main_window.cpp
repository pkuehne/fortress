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
        events()->raise(std::make_shared<RegisterWindowEvent>(
            std::make_shared<GeneratorWindow>(true),
            RegisterWindowEvent::WindowAction::Replace));
    };
    Label::CommandCharCB create = [=](Label* l) {
        events()->raise(std::make_shared<RegisterWindowEvent>(
            std::make_shared<GeneratorWindow>(false),
            RegisterWindowEvent::WindowAction::Replace));
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
            events()->raise(std::make_shared<RegisterWindowEvent>(
                std::make_shared<LoadWindow>()));
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
