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

    std::string newGame ("Quickstart!");
    std::string newWorld ("Create New World");
    std::string loadGame ("Load Existing World");
    std::string tutorial ("Start The Tutorial");

    int line = getHeight() - 15;
    int spacing = 3;
    Color darkGrey (GREY);
    darkGrey.Red()   *= 0.3;
    darkGrey.Green() *= 0.3;
    darkGrey.Blue()  *= 0.3;
    Color darkGreen (GREEN);
    darkGreen.Red()   *= 0.3;
    darkGreen.Green() *= 0.3;
    darkGreen.Blue()  *= 0.3;

    drawString (line, (getWidth()/2) - (newGame.length()/2), newGame.c_str());
    drawTile (line, (getWidth()/2) - (newGame.length()/2), 'Q', Color (GREEN), Color (BLACK));
    drawString (line += spacing, (getWidth()/2) - (newWorld.length()/2), newWorld.c_str());
    drawTile (line, (getWidth()/2) - (newWorld.length()/2), 'C', Color (GREEN), Color (BLACK));
    drawString (line += spacing, (getWidth()/2) - (loadGame.length()/2), loadGame.c_str());
    drawTile (line, (getWidth()/2) - (loadGame.length()/2), 'L', Color(GREEN), Color (BLACK));
    drawString (line += spacing, (getWidth()/2) - (tutorial.length()/2), tutorial.c_str(), darkGrey, Color (BLACK));
    drawTile (line, (getWidth()/2) - (tutorial.length()/2), 'S', darkGreen, Color (BLACK));

}

void MainWindow::keyDown (unsigned char key) {
    if (key == ESC) {
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
