#include "main_window.h"
#include "map_window.h"
#include "generator_window.h"
#include "game_engine.h"
#include "file_loader.h"

void MainWindow::registerWidgets()
{
    setTitle (" FORTRESS ");

    Label* l = nullptr;
    l = this->createWidget<Label>(1, 15);
    l->text("Quickstart");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>(1, 12);
    l->text("Create New World");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>(1, 9);
    l->text("Load Existing World");
    l->commandChar = 1;
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->hAlign = Widget::HorizontalAlign::Centre;

    l = this->createWidget<Label>(1, 6);
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
        GeneratorWindow* l_win = new GeneratorWindow();
        l_win->initialise (getEngine(), (void*)1);

        getEngine()->getWindows()->pushWindow (l_win);
    }

    if (key == 'c' || key == 'C') {
        GeneratorWindow* l_win = new GeneratorWindow();
        l_win->initialise (getEngine());

        getEngine()->getWindows()->pushWindow (l_win);
    }

    if (key == 'l' || key == 'L') {
        MapWindow* l_win = new MapWindow();
        l_win->initialise (getEngine());

        FileLoader loader;
        loader.initialise (getEngine());
        loader.loadState();
        getEngine()->getWindows()->pushWindow (l_win);
    }
}
