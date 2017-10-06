#include "main_window.h"
#include "map_window.h"
#include "generator_window.h"
#include "game_engine.h"
#include "file_loader.h"

void MainWindow::gainFocus () {
    setTitle (" FORTRESS ");

}

void MainWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
}

void MainWindow::redraw() {
    int yPos = getHeight() - 18;
    int spacing = 3;

    drawCommandString (yPos += spacing, -1, "Quickstart!", 0);
    drawCommandString (yPos += spacing, -1, "Create New World", 0);
    drawCommandString (yPos += spacing, -1, "Load Existing World", 0);
    drawCommandString (yPos += spacing, -1, "Start The Tutorial", 0, false);

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
