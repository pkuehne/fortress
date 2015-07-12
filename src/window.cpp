#include "window.h"
#include "game_engine_interface.h"

void Window::initialise (GameEngineInterface* a_engine)
{
    m_engine = a_engine;
}

void Window::beforeRedraw()
{
    m_engine->getGraphics()->beginScreenUpdate();
}

void Window::afterRedraw()
{
    m_engine->getGraphics()->endScreenUpdate();
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
