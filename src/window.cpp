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

void Window::drawString (int y, int x, const char* text)
{
    getEngine()->getGraphics()->drawString (m_yOffset+y, m_xOffset+x, text);
}

void Window::beforeRedraw()
{
    getEngine()->getGraphics()->clearArea (m_yOffset, m_xOffset, m_height, m_width);
    getEngine()->getGraphics()->drawBorder (m_yOffset, m_xOffset, m_height, m_width);
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
