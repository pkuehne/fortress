#include "splash_window.h"
#include "map_window.h"
#include "gameengine.h"
#include "graphics.h"

void SplashWindow::redraw() {

    Color grey (GREY);

    int xOffset = 12;
    int yOffset = 20;

    drawString (yOffset - 3, xOffset + 15, "Welcome to");


    // 'F'
    drawTile ( yOffset +  0,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  0,  xOffset +  1, 246, grey, grey);
    drawTile ( yOffset +  0,  xOffset +  2, 246, grey, grey);
    drawTile ( yOffset +  0,  xOffset +  3, 246, grey, grey);

    drawTile ( yOffset +  1,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  2,  xOffset +  0, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset +  1, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset +  2, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset +  0, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset +  0, 246, grey, grey);

    // 'o'
    drawTile ( yOffset +  3,  xOffset +  5, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset +  5, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset +  5, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset +  5, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset +  5, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset +  8, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset +  8, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset +  8, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset +  8, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset +  8, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset +  6, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset +  7, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset +  6, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset +  7, 246, grey, grey);

    // 'r'
    drawTile ( yOffset +  3,  xOffset + 11, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 11, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 11, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 11, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 11, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 12, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset + 13, 246, grey, grey);

    // 't'
    drawTile ( yOffset +  0,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  1,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  2,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 17, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 17, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 16, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset + 18, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 18, 246, grey, grey);

    // 'r'
    drawTile ( yOffset +  3,  xOffset + 21, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 21, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 21, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 21, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 21, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 22, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset + 23, 246, grey, grey);

    // 'e'
    drawTile ( yOffset +  3,  xOffset + 26, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 26, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 26, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 26, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 26, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 29, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 29, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 29, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 29, 246, grey, grey);


    drawTile ( yOffset +  5,  xOffset + 27, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 28, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 27, 246, grey, grey);
    drawTile ( yOffset +  3,  xOffset + 28, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 27, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 28, 246, grey, grey);

    // 's'
    drawTile ( yOffset +  3,  xOffset + 32, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 32, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 32, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 32, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 34, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 34, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 34, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 34, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 33, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 33, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 33, 246, grey, grey);

    // 's'
    drawTile ( yOffset +  3,  xOffset + 37, 246, grey, grey);
    drawTile ( yOffset +  4,  xOffset + 37, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 37, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 37, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 39, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 39, 246, grey, grey);
    drawTile ( yOffset +  6,  xOffset + 39, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 39, 246, grey, grey);

    drawTile ( yOffset +  3,  xOffset + 38, 246, grey, grey);
    drawTile ( yOffset +  5,  xOffset + 38, 246, grey, grey);
    drawTile ( yOffset +  7,  xOffset + 38, 246, grey, grey);



    if (!getKey(' ')) return;
    MapWindow* l_win = new MapWindow();
    l_win->initialise();

    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->getWindows().replaceWindow (l_win);
}
