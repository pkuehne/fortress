#include "window.h"
#include "game_engine_interface.h"
#include <iostream>

void Window::initialise (GameEngineInterface* a_engine, void* args, void* retval)
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
    return getEngine()->getGraphics()->drawString (m_yOffset+y, m_xOffset+x, text, fg, bg);
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