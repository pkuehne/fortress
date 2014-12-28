#include "window.h"
#include "graphics.h"
#include "gameengine.h"
#include "algorithm.h" 
#include "lodepng/lodepng.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>

static int s_mapXOffset = 0;
static int s_mapYOffset = 80;
static int s_tileSize   = 20;

// Temporary test functions
void demoPath (int x, int y)
{
    GameEngine* l_engine = GameEngine::getEngine();
    Unit& l_unit = l_engine->getUnits().getUnit(0);
    l_unit.setNewDestination (x, y);
}

void toggleUnitSwim (void)
{
    GameEngine* l_engine = GameEngine::getEngine();
    Unit& l_unit = l_engine->getUnits().getUnit(0);
    l_unit.canSwim() = ! l_unit.canSwim();
}

int Window::screenXToMapX (int screenX)
{
    return ((screenX - s_mapXOffset) / s_tileSize) + m_mapX;
}

int Window::screenYToMapY (int screenY)
{
    return ((screenY - s_mapYOffset) / s_tileSize) + m_mapY;
}

int Window::mapXToScreenX (int mapX)
{
    return ((mapX - m_mapX) * s_tileSize) + s_mapXOffset;
}

int Window::mapYToScreenY (int mapY)
{
    return ((mapY - m_mapY) * s_tileSize) + s_mapYOffset;
}

void Window::loadImages ()
{
    m_backgrounds[TILE_PLAIN] 
        = loadImage ("../images/rendered/bg-grass.png");
    m_backgrounds[TILE_WATER] 
        = loadImage ("../images/rendered/bg-water.png");

    m_constructions[CON_WALL]
        = loadImage ("../images/rendered/cn-wall.png");

    m_units[UNIT_WARRIOR]
        = loadImage ("../images/rendered/un-warrior.png");
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
    int max = GameEngine::getEngine()->getMap().getMapHeight() - m_mapHeight + 1;
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
    int max = GameEngine::getEngine()->getMap().getMapWidth() - m_mapWidth + 1;
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
    int maxHeight = GameEngine::getEngine()->getMap().getMapHeight();
    int maxWidth  = GameEngine::getEngine()->getMap().getMapWidth();

    m_mapHeight = (height - s_mapYOffset) / s_tileSize;
    m_mapWidth  = (width - s_mapXOffset) / s_tileSize;
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
    if (ascii_keys['n']) m_showNames = !m_showNames;
    if (ascii_keys['c']) toggleUnitSwim();
    //glutPostRedisplay();
}

void Window::keyUp (unsigned char key)
{
    ascii_keys[key] = false;
    //glutPostRedisplay();
}

void Window::mouseDown (int x, int y, int button)
{
    demoPath (screenXToMapX(x), screenYToMapY(y));
}

void Window::mouseUp (int x, int y, int button)
{
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

//void Window::mapTileToImage
void Window::drawMap () {
    GameEngine* l_engine = GameEngine::getEngine();
    const Map&  l_map = l_engine->getMap();
    Screen l_screen = l_engine->getScreen();
    
    for (int hh = m_mapY; hh < m_mapY + m_mapHeight; hh++) {
        for (int ww = m_mapX; ww < m_mapX + m_mapWidth; ww++) {
            const Tile& l_tile = l_map.getTile (ww, hh); 
            // Draw background
            drawImage (
                mapXToScreenX (ww), 
                mapYToScreenY (hh),
                m_backgrounds[l_tile.getBackground()]);

            if (l_tile.getConstruction() != CON_EMPTY) {
                // Draw Construction
                drawImage (
                    mapXToScreenX (ww), 
                    mapYToScreenY (hh),
                    m_constructions[l_tile.getConstruction()]);
            }
        }
    }
}

void Window::drawUnits () {
    GameEngine* l_engine = GameEngine::getEngine();
    UnitList& l_units = l_engine->getUnits();

    for (int ii = 0; ii < l_units.getNumUnits(); ii++)
    {
        Unit& l_unit = l_units.getUnit (ii);
        if ((l_unit.getX() >= m_mapX && 
                l_unit.getX() < m_mapWidth + m_mapX) &&
            (l_unit.getY() >= m_mapY && 
                l_unit.getY() < m_mapHeight + m_mapY)) { 

            drawImage (
                mapXToScreenX (l_unit.getX()), 
                mapYToScreenY (l_unit.getY()),
                m_units[l_unit.getType()]);
            if (l_unit.getHitPoints() <= 0) {
                drawString (
                    mapXToScreenX (l_unit.getX()), 
                    mapYToScreenY (l_unit.getY()),
                    "Dead");
            } else if (l_unit.getTarget()) {
                drawString (
                    mapXToScreenX (l_unit.getX()), 
                    mapYToScreenY (l_unit.getY()),
                    "Fighting");
            } else if (m_showNames) {
                std::string l_name ("Warrior");
                if (l_unit.canSwim()) l_name.append (" Swimmer");
                drawString (
                    mapXToScreenX (l_unit.getX()), 
                    mapYToScreenY (l_unit.getY()),
                    l_name.c_str());
            }
        }
    }
}

