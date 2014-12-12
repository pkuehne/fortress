#include "window.h"
#include "graphics.h"
#include "gameengine.h"
#include "algorithm.h"
#include "lodepng/lodepng.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>

static int mapXOffset = 0;
static int mapYOffset = 80;

void Window::loadImages ()
{
    m_backgrounds[TILE_PLAIN] 
        = loadImage ("../images/rendered/bg-grass.png");
    m_backgrounds[TILE_WATER] 
        = loadImage ("../images/rendered/bg-water.png");

    m_constructions[CON_WALL]
        = loadImage ("../images/rendered/cn-wall.png");

    m_units[UNIT_WARRIOR]
        = loadImage ("../images/rendered/test-bg.png");
}

void Window::initialise (void)
{
    loadImages ();
    m_mapHeight = 30;
    m_mapWidth  = 30;
    m_mapX = 1;
    m_mapY = 1;
}

void Window::setMapY (int newY)
{
    int max = GameEngine::getEngine()->getMap().getMaxHeight() - m_mapHeight + 1;
    if (newY > max) {
        m_mapY = max;
    } else if (newY < 1) {
        m_mapY = 1;
    } else {
        m_mapY = newY;
    }
}

void Window::setMapX (int newX)
{
    int max = GameEngine::getEngine()->getMap().getMaxWidth() - m_mapWidth + 1;
    if (newX > max) {
        m_mapX = max;
    } else if (newX < 1) {
        m_mapX = 1;
    } else {
        m_mapX = newX;
    }

}

void Window::destroy (void)
{

}

void Window::resize (int width, int height)
{
    int maxHeight = GameEngine::getEngine()->getMap().getMaxHeight();
    int maxWidth  = GameEngine::getEngine()->getMap().getMaxWidth();

    m_mapHeight = (height - mapYOffset) / 20;
    m_mapWidth  = (width - mapXOffset) / 20;
    if (m_mapHeight > maxHeight) m_mapHeight = maxHeight;
    if (m_mapWidth > maxWidth) m_mapWidth = maxWidth;

    if (m_mapY + m_mapHeight > maxHeight) {
        setMapY (maxHeight - m_mapHeight + 1);
    }
    if (m_mapX + m_mapWidth > maxWidth) {
        setMapX (maxWidth - m_mapWidth + 1);
    }
}

void Window::keyDown (unsigned char key)
{
    ascii_keys[key] = true;
    //glutPostRedisplay();
}

void Window::keyUp (unsigned char key)
{
    ascii_keys[key] = false;
    //glutPostRedisplay();
}

void demoPath (int x, int y)
{
    GameEngine* l_engine = GameEngine::getEngine();
    Unit& l_unit = l_engine->getUnits().getUnit(0);
    std::vector<int> l_path;
    Algorithm::findPath (   Map::getIndex (l_unit.getX(),l_unit.getY()), 
                            Map::getIndex (x, y), 
                            l_path);
    l_unit.setNewPath (l_path);
}

void Window::processKeys ()
{
    GameEngine* l_engine = GameEngine::getEngine();
    const Map&  l_map = l_engine->getMap();
    Screen& l_screen = l_engine->getScreen();

    if (ascii_keys[27]) exit (0); // for now
    if (ascii_keys['w']) setMapY (m_mapY - 1);
    if (ascii_keys['s']) setMapY (m_mapY + 1);
    if (ascii_keys['a']) setMapX (m_mapX - 1);
    if (ascii_keys['d']) setMapX (m_mapX + 1);
    if (ascii_keys['r']) demoPath (9, 7);
    if (ascii_keys['t']) demoPath (9, 11);
}

void Window::redraw ()
{
    processKeys();
    drawTitle();
    drawMap();
    drawUnits();

    glFlush();
}

void Window::drawTitle ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (ascii_keys['f']) {
        glColor3f (1.0, 0.0, 0.0);
    } else {
        glColor3f (1.0, 1.0, 1.0);
    }
    printString (30, 2, "WELCOME TO FORTRESS");
}

void Window::drawMap () {
    GameEngine* l_engine = GameEngine::getEngine();
    const Map&  l_map = l_engine->getMap();
    Screen l_screen = l_engine->getScreen();
    
    //std::cout 
    //    << " MapY = " << m_mapY 
    //    << " MapX = " << m_mapX 
    //    << std::endl;

    for (int hh = m_mapY; hh < m_mapY + m_mapHeight; hh++) {
        for (int ww = m_mapX; ww < m_mapX + m_mapWidth; ww++) {
            const Tile& l_tile = l_map.getTile (ww, hh); 
            //std::cout 
            //    << " H: " << hh 
            //    << " W: " << ww
            //    << " T: " << l_tile.getBackground() << std::endl;

            // Draw background
            drawImage (
                ((ww - m_mapX) * 20) + mapXOffset, 
                ((hh - m_mapY) * 20) + mapYOffset,
                m_backgrounds[l_tile.getBackground()]);

            if (l_tile.getConstruction() != CON_EMPTY) {
                drawImage (
                    ((ww - m_mapX) * 20) + mapXOffset, 
                    ((hh - m_mapY) * 20) + mapYOffset,
                    m_constructions[l_tile.getConstruction()]);
            }
            // Draw construction
        }
    }
}

void Window::drawUnits () {
    GameEngine* l_engine = GameEngine::getEngine();
    UnitList& l_units = l_engine->getUnits();

    UnitVector::iterator iter = l_units.getUnits().begin();
    for (; iter != l_units.getUnits().end(); iter++)
    {
        Unit l_unit = *iter;
        if ((l_unit.getX() >= m_mapX && 
                l_unit.getX() < m_mapWidth + m_mapX) &&
            (l_unit.getY() >= m_mapY && 
                l_unit.getY() < m_mapHeight + m_mapY)) { 

            drawImage (
                ((l_unit.getX() - m_mapX) * 20) + mapXOffset, 
                ((l_unit.getY() - m_mapY) * 20) + mapYOffset,
                m_units[l_unit.getType()]);
        }
    }
}

