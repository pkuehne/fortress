#include "debug_window.h"
#include "game_engine.h"

void DebugWindow::gainFocus()
{
    setTitle (" Debug Console ");
    command[0] = '\0';
}

void DebugWindow::redraw()
{
    std::vector<Output>::reverse_iterator iter = history.rbegin();
    int offset = 7;
    for (; iter != history.rend(); iter++) {
        drawString (getHeight() - offset++, 3, iter->text.c_str(), iter->color);
    }

    drawBorder (getHeight()-5, 0, 3, getWidth()-2);
    drawString (getHeight()-3, 3, "Command:");
    drawString (getHeight()-3, 12, command);
    drawString (getHeight()-3, 12 + length, "#", Color(RED));
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
        return;
    }
    if (key == KEY_ENTER) {
        Output line;
        line.text = std::string(command);
        line.color = COMMAND_COLOR;
        history.push_back (line);

        // Execute command

        command[length=0] = '\0';
        return;
    }
    if (key == KEY_BACKSPACE) {
        command[--length] = '\0';
        return;
    }
    command[length] = key;
    command[++length] = '\0';
    std::cout << "Key: " << key << " Command: " << command << std::endl;
}
