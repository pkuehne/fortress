#include "splash_window.h"
#include "map_window.h"
#include "gameengine.h"
#include "graphics.h"

void SplashWindow::redraw() {

    drawString (1, 23, "This is my fortress!");

    if (!getKey(' ')) return;
    MapWindow* l_win = new MapWindow();
    l_win->initialise();

    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->getWindows().replaceWindow (l_win);
}
