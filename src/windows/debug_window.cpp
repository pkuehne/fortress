#include "debug_window.h"
#include "game_engine.h"

void DebugWindow::gainFocus()
{
    setTitle (" Debug Console ");
}

void DebugWindow::redraw()
{
    drawString (getHeight()-3, 2, "Command:");
    drawBorder (getHeight()-5, 0, 3, getWidth()-2);
    drawString (getHeight()-3, 11, command.c_str(), Color(RED));
    drawString (getHeight()-3, 11+command.size(), "#", Color(RED));
}

void DebugWindow::resize()
{
    setDimensions (0, 0, 
            getEngine()->getGraphics()->getScreenWidth() - 6, 
            getEngine()->getGraphics()->getScreenHeight() - 6);
}

void DebugWindow::keyDown (unsigned char key)
{
    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
