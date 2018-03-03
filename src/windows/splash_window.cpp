#include "splash_window.h"
#include "main_window.h"
#include "../core/game_engine.h"
#include "../core/graphics.h"

void SplashWindow::setup() {
    setFullscreen(true);
}

void SplashWindow::registerWidgets()
{

}

void SplashWindow::redraw() {

    Color grey (GREY);

    int xOffset = getWidth()/2 - 19;
    int yOffset = getHeight()/2;

    getEngine()->getGraphics()->drawString (yOffset - 3, xOffset + 19 - 5, "Welcome to");

    int tile = 178;

    // 'F'
    getEngine()->getGraphics()->drawTile ( yOffset +  0,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  0,  xOffset +  1, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  0,  xOffset +  2, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  0,  xOffset +  3, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  1,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  2,  xOffset +  0, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  1, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  2, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset +  0, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset +  0, tile, grey, grey);

    // 'o'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  5, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset +  5, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset +  5, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset +  5, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset +  5, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  8, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset +  8, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset +  8, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset +  8, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset +  8, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  6, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset +  7, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset +  6, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset +  7, tile, grey, grey);

    // 'r'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 11, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 11, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 11, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 11, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 11, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 12, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 13, tile, grey, grey);

    // 't'
    getEngine()->getGraphics()->drawTile ( yOffset +  0,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  1,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  2,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 17, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 17, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 16, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 18, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 18, tile, grey, grey);

    // 'r'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 21, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 21, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 21, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 21, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 21, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 22, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 23, tile, grey, grey);

    // 'e'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 26, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 26, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 26, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 26, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 26, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 29, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 29, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 29, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 29, tile, grey, grey);


    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 27, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 28, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 27, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 28, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 27, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 28, tile, grey, grey);

    // 's'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 32, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 32, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 32, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 32, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 34, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 34, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 34, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 34, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 33, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 33, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 33, tile, grey, grey);

    // 's'
    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 37, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  4,  xOffset + 37, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 37, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 37, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 39, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 39, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  6,  xOffset + 39, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 39, tile, grey, grey);

    getEngine()->getGraphics()->drawTile ( yOffset +  3,  xOffset + 38, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  5,  xOffset + 38, tile, grey, grey);
    getEngine()->getGraphics()->drawTile ( yOffset +  7,  xOffset + 38, tile, grey, grey);

}

void SplashWindow::keyDown (unsigned char key) {
    //if (!getKey(' ')) return;
    MainWindow* l_win = new MainWindow();
    l_win->initialise(getEngine());

    getEngine()->getWindows()->replaceAllWindows (l_win);
}
