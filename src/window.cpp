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

}

void Window::mouseUp (int x, int y, int button)
{

}
