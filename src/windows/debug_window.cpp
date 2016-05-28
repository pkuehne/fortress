#include "debug_window.h"
#include "game_engine.h"
#include <dirent.h>

const char CONSOLE_DIR[] = "./scripts/console";

void DebugWindow::gainFocus()
{
    setTitle (" Debug Console ");
    command[0] = '\0';
    m_lua.setGameState(getEngine()->state());
    try {
        loadLuaScripts();
    } catch (const std::runtime_error& error) {
        Output line (error.what(), ERROR_COLOR);
        history.push_back (line);
    }
}

void DebugWindow::loadLuaScripts()
{
    DIR* directory = opendir (CONSOLE_DIR);
    if (directory == nullptr) {
        LOG(ERROR) << "Failed to open '"
            << CONSOLE_DIR << "'"
            << std::endl;
        throw std::runtime_error ("Failed to open console directory");
    }
    struct dirent* file = nullptr;
    while ((file = readdir (directory)) != nullptr) {
        std::string filename (CONSOLE_DIR);
        filename.append ("/").append(file->d_name);
        if (filename.find (".lua") != std::string::npos) {
            LOG(INFO) << "Loading lua script: " << filename << std::endl;
            try {
                m_lua.loadFile (filename);
                Output line (std::string("Loaded: ").append (filename), OUTPUT_COLOR);
                history.push_back (line);
            } catch (const std::runtime_error& error) {
                Output line (error.what(), ERROR_COLOR);
                history.push_back (line);
            }
        }
    }
    closedir (directory);
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
        command[length=0] = '\0';

        // Execute command
        try {
            line.text = std::string(">>>").append (
                    m_lua.executeCommand (line.text));
            line.color = OUTPUT_COLOR;
        } catch (std::runtime_error& error) {
            line.text = std::string(">>>").append (
                    error.what());
            line.color = ERROR_COLOR;
        }
        history.push_back (line);
        //std::cout << "Command output: " << line.text << std::endl;
        return;
    }
    if (key == KEY_BACKSPACE) {
        if (length > 0) {
            command[--length] = '\0';
        }
        return;
    }
    command[length] = key;
    command[++length] = '\0';
}
