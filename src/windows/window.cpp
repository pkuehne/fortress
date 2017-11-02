#include "window.h"
#include "../core/game_engine.h"
#include <iostream>

void Window::initialise (GameEngine* a_engine, void* args, void* retval)
{
    m_engine    = a_engine;
    m_args      = args;
    m_retval    = retval;
    setDimensions (2, 2, 2, 2);
}

void Window::setDimensions (int x, int y, int width, int height)
{
    m_xOffset   = x;
    m_yOffset   = y;
    m_width     = width;
    m_height    = height;

    getEngine()->getGraphics()->calculateWindowOffsetsFromCentre (height, width, y, x);
    if (m_xOffset == 0) {
        m_xOffset = x;
    }
    if (m_yOffset == 0) {
        m_yOffset = y;
    }
}

unsigned int Window::drawString (int y, int x, const char* text, Color fg, Color bg)
{
    if (x < 0) x = (m_width/2) - (strlen(text)/2);
    return getEngine()->getGraphics()->drawString (m_yOffset+y, m_xOffset+x, text, fg, bg);
}

unsigned int Window::drawCommandString (int y, int x, const char* text, int pos, bool active)
{
    char command[2] = {0};
    if (x < 0)
        x = (m_width/2) - (strlen(text)/2);
    Color fg = Color(WHITE);
    Color bg = Color(BLACK);
    Color cc = Color(GREEN);
    if (!active) {
        float factor = 0.5;
        fg *= factor;
        cc *= factor;
    }

    unsigned int retval = drawString (y, x, text, fg, bg);
    command[0] = text[pos];
    retval += drawString (y, x+pos, command, cc, bg);
    return retval;
}

void Window::drawTile (int y, int x, unsigned int tile, Color fg, Color bg)
{
    getEngine()->getGraphics()->drawTile (m_yOffset+y, m_xOffset+x, tile, fg, bg);
}

void Window::drawBorder (int y, int x, int height, int width) {
    getEngine()->getGraphics()->drawBorder (m_yOffset+y, m_xOffset+x, height, width);
}

void Window::clearArea (int y, int x, int height, int width) {
    getEngine()->getGraphics()->clearArea (m_yOffset+y, m_xOffset+x, height, width);
}

void Window::beforeRedraw()
{
    getEngine()->getGraphics()->clearArea (m_yOffset, m_xOffset, m_height, m_width);
    getEngine()->getGraphics()->drawBorder (m_yOffset, m_xOffset, m_height-2, m_width-2);

    int x, y;
    getEngine()->getGraphics()->calculateWindowOffsetsFromCentre (0, m_title.size(), y, x);
    getEngine()->getGraphics()->clearArea (m_yOffset, x, 1, m_title.size());
    drawString (0, x-m_xOffset, m_title.c_str());

}

void Window::renderWidgets()
{
    for (auto iter : m_widgets) {
        Widget* w = iter.second;
        if(!w) continue;
        w->realignWidget(m_width-2, m_height-2);
        w->render();
    }
}

void Window::afterRedraw()
{

}

void Window::destroy (void)
{
}

void Window::resize (int width, int height)
{

}

void Window::mouseDown (int x, int y, int button)
{
    if (button < MAX_BUTTONS) {
        m_buttons[button] = true;
    }
}

void Window::mouseUp (int x, int y, int button)
{
    if (button < MAX_BUTTONS) {
        m_buttons[button] = false;
    }
}

bool Window::getMouseButton (int button)
{
    if (button < MAX_BUTTONS) {
        return m_buttons[button];
    }
    return false;
}

void Window::drawProgress (unsigned int x, unsigned int y, unsigned int value, unsigned int max)
{
    float l_value = (float) value;
    float l_max = (float) max;
    Color l_color ((1.0f-(l_value/l_max)), l_value/l_max, 0);

    for (unsigned int xx = 0; xx < value; xx++) {
        drawTile (y, x+xx, 178, l_color, Color(BLACK));
    }
}

unsigned int Window::wrapText (const std::string& text, std::vector<std::string>& lines, unsigned int maxWidth, unsigned int maxRows)
{
    size_t wordStart = 0;
    size_t wordEnd = 0;
    unsigned int lineNum = 0;
    lines.resize (maxRows);

    while (wordEnd != std::string::npos) {
        wordEnd = text.find (' ', wordStart);
        std::string word (text.substr (wordStart, wordEnd-wordStart));
        if (lines[lineNum].length() + word.length() + 3 /*...*/ + 2 /*spaces*/ > maxWidth && lineNum + 1 >= maxRows) {
            lines[lineNum].append ("...");
            return lineNum;
        }
        if (lines[lineNum].length() + word.length() + 1 > maxWidth) {
            if (lineNum + 1 >= maxRows) {
                lines[lineNum].append ("...");
                return lineNum;
            }
            // Start the next line
            lineNum++;
        }
        lines[lineNum].append (word);
        lines[lineNum].append (" ");
        wordStart = wordEnd+1;
    }

    return lineNum;
}

void Window::keyDown (unsigned char key)
{
    ascii_keys[key] = true;

    for (auto iter : m_widgets) {
        iter.second->keyDown(key);
    }
    this->keyPress(key);
}
