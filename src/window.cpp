#include "window.h"
#include "game_engine_interface.h"

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
