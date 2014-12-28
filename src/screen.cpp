#include "screen.h"
#include "graphics.h"
#include "gameengine.h"
#include "window.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

Screen::Screen ()
: m_mapWindow ()
, m_screenHeight (600)
, m_screenWidth (800)
{
}

Screen::~Screen()
{
}

void Screen::initialise ()
{
    setup_graphics();
}

void Screen::start ()
{
    m_mapWindow.initialise();
    start_graphics();
}

void Screen::keyDown (unsigned char key)
{
    m_mapWindow.keyDown (key);
}

void Screen::keyUp (unsigned char key)
{
    m_mapWindow.keyUp (key);
}

void Screen::mouseDown (int x, int y, int button)
{
    m_mapWindow.mouseDown (x, y, button);
}

void Screen::mouseUp (int x, int y, int button)
{
    m_mapWindow.mouseUp (x, y, button);
}

void Screen::redraw ()
{
    m_mapWindow.redraw ();
}

void Screen::resize (int width, int height)
{
    m_mapWindow.resize (width, height);
}
