#include "main_window.h"
#include "../core/file_loader.h"
#include "../core/game_engine.h"
#include "generator_window.h"
#include "label.h"
#include "map_window.h"

void MainWindow::setup() {
    setTitle("FORTRESS");
    setFullscreen();
    setEscapeBehaviour(Window::EscapeBehaviour::QuitGame);
}
void MainWindow::registerWidgets() {
    Label::CommandCharCB quickstart = [=](Label* l) {
        auto args = std::make_shared<GeneratorWindowArgs>();
        args->hideWindow = true;
        getEngine()->getWindows()->createWindow<GeneratorWindow>(args);
    };
    Label::CommandCharCB create = [](Label* l) {
        auto args = std::make_shared<GeneratorWindowArgs>();
        args->hideWindow = false;
        l->getWindow()
            ->getEngine()
            ->getWindows()
            ->createWindow<GeneratorWindow>(args);
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
            std::cout << "Loading" << std::endl;
            FileLoader loader(getEngine()->state());
            loader.loadState("./data/saves/test.yaml");
            
            MapWindow* l_win = new MapWindow();
            l_win->initialise(getEngine());
            getEngine()->getWindows()->replaceAllWindows(l_win);
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
