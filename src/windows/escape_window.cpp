#include "escape_window.h"
#include "game_engine.h"

void EscapeWindow::gainFocus()
{
    setTitle (" FORTRESS ");
}

void EscapeWindow::redraw()
{
    int y = 2;
    drawString (y++, -1, "Press ESC to return");
    drawCommandString (y++, -1, "Save Game", 0, false);
    drawCommandString (y++, -1, "Reload Config", 0, false);
    drawCommandString (y++, -1, "Quit Game", 0);
}

void EscapeWindow::resize()
{
    setDimensions (0, 0, 
            getEngine()->getGraphics()->getScreenWidth(), 
            getEngine()->getGraphics()->getScreenHeight());
}

void EscapeWindow::keyDown (unsigned char key)
{
    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
    }
    if (toupper(key) == 'Q') {
        getEngine()->quit();
    }
}
