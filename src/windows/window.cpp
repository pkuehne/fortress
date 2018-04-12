#include "window.h"
#include "frame.h"
#include "../core/game_engine.h"
#include <iostream>

void Window::initialise(GameEngine *a_engine, void *args, void *retval)
{
    m_engine = a_engine;
    m_graphics = m_engine->getGraphics();
    m_state = m_engine->state();
    m_manager = m_engine->getWindows();
    m_args = args;
    m_retval = retval;
    m_baseWidget = createWidget<Frame>("frmBase", 0, 0)->setBorder(true);
}

void Window::setDimensions(int x, int y, int width, int height)
{
    m_xOffset = x;
    m_yOffset = y;
    m_width = width;
    m_height = height;

    m_baseWidget
        ->setWindowOffsets(m_xOffset, m_yOffset) // TODO: Remove
        ->setHeight(m_height)
        ->setWidth(m_width)
        ->realign(x, y, width, height);
}

void Window::beforeRedraw()
{
    m_graphics->clearArea(m_yOffset, m_xOffset, m_height, m_width);
}

void Window::renderWidgets()
{
    m_baseWidget->render();
}

void Window::afterRedraw()
{
}

void Window::destroy(void)
{
}

/// The "screen" dimensions have changed, reload them and re-apply depending on whether this window is fullscreen or not
void Window::resize()
{
    if (m_fullscreen)
    {
        setDimensions(0, 0, m_graphics->getScreenWidth(), m_graphics->getScreenHeight());
    }
    else
    {
        int x = 0;
        int y = 0;

        m_graphics->calculateWindowOffsetsFromCentre(m_height, m_width, y, x);
        m_xOffset = x;
        m_yOffset = y;
        setDimensions(x, y, m_width, m_height);
    }
}

void Window::mouseDown(int x, int y, int button)
{
    if (button < MAX_BUTTONS)
    {
        m_buttons[button] = true;
    }
}

void Window::mouseUp(int x, int y, int button)
{
    if (button < MAX_BUTTONS)
    {
        m_buttons[button] = false;
    }
}

bool Window::getMouseButton(int button)
{
    if (button < MAX_BUTTONS)
    {
        return m_buttons[button];
    }
    return false;
}

void Window::keyDown(unsigned char key)
{
    ascii_keys[key] = true;

    if (m_onEscape != EscapeBehaviour::None && key == KEY_ESC)
    {
        if (m_onEscape == EscapeBehaviour::CloseWindow)
        {
            getEngine()->getWindows()->popWindow();
        }
        if (m_onEscape == EscapeBehaviour::QuitGame)
        {
            getEngine()->quit();
        }
        return;
    }

    m_baseWidget->keyPress(key);
    this->keyPress(key);
}

void Window::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
    setDimensions(0, 0, m_graphics->getScreenWidth(), m_graphics->getScreenHeight());
}

void Window::setTitle(const std::string &title)
{
    dynamic_cast<Frame*>(m_baseWidget)->setTitle(title);
}
