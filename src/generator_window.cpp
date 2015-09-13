#include "generator_window.h"
#include "gameengine.h"

void GeneratorWindow::gainFocus () {
    setTitle (" Create New World ");

}

void GeneratorWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
}

void GeneratorWindow::redraw() {

}

void GeneratorWindow::keyDown (unsigned char key) {
    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
