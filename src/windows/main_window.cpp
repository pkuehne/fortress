#include "main_window.h"
#include "map_window.h"
#include "generator_window.h"
#include "game_engine.h"
#include "file_loader.h"

void MainWindow::registerWidgets()
{
    setTitle (" FORTRESS ");

    Label* l = nullptr;
    l = this->createWidget<Label>("lblQuickstart", 1, 15);
    l->text("Quickstart");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>("lblCreate", 1, 12);
    l->text("Create New World");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>("lblLoad", 1, 9);
    l->text("Load Existing World");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>("lblTutorial", 1, 6);
    l->text("Start The Tutorial");
    l->commandChar = 1;
    l->sensitive = false;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;
}

void MainWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
}

void MainWindow::keyDown (unsigned char key) {
    if (key == KEY_ESC) {
        getEngine()->quit();
    }

    if (key == 'q' || key == 'Q') {
        getEngine()->getWindows()->createWindow<GeneratorWindow>((void*)1);
    }

    if (key == 'c' || key == 'C') {
        getEngine()->getWindows()->createWindow<GeneratorWindow>();
    }

    if (key == 'l' || key == 'L') {
        // Load a file - then show the map
        //FileLoader loader;
        //loader.initialise (getEngine());
        //loader.loadState();
        getEngine()->getWindows()->createWindow<MapWindow>();
    }
}
