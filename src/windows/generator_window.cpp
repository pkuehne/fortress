#include "generator_window.h"
#include "../core/game_engine.h"
#include "../generators/dungeon_generator.h"
#include "../generators/rural_generator.h"
#include "map_window.h"
#include "../components/stair_component.h"
#include <sstream>
#include <glog/logging.h>

std::string GeneratorWindow::formatNumber (int number) {
    std::stringstream str;

    if (number < 10) str << " ";
    if (number < 100) str << " ";
    str << number;
    return str.str();
}

void GeneratorWindow::setup() {
    m_levelWidth = 30;
    m_levelHeight = 30;
    m_levelDepth = 2;
    m_levelRooms = 2;
    m_worldSize = 129;
    m_selectedPosition = WIDTH;
    m_status = WAITING;

    setTitle (" Create New World ");
    setFullscreen(true);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void GeneratorWindow::registerWidgets() {

}

void GeneratorWindow::redraw() {

    if (getArgs()) return;

    int middleX = getWidth()/2;
    int middleY = getHeight();
    int selY    = 0;

    drawString (middleY - 11, middleX - 10, "Level Parameters:");
    drawString (middleY - 10, middleX - 6, "Width: ");
    if (m_status == WAITING) drawTile (middleY - 10, middleX - 6, 'W', Color (GREEN), Color (BLACK));
    drawString (middleY - 10, middleX + 2, formatNumber(m_levelWidth).c_str());
    if (m_selectedPosition == WIDTH) selY = middleY - 10;
    drawString (middleY - 9, middleX - 6, "Height: ");
    if (m_status == WAITING) drawTile (middleY - 9, middleX - 6, 'H', Color (GREEN), Color (BLACK));
    drawString (middleY - 9, middleX + 2, formatNumber(m_levelHeight).c_str());
    if (m_selectedPosition == HEIGHT) selY = middleY - 9;

    drawString (middleY - 8, middleX - 6, "Rooms: ");
    if (m_status == WAITING) drawTile (middleY - 8, middleX - 6, 'R', Color (GREEN), Color (BLACK));
    drawString (middleY - 8, middleX + 2, formatNumber(m_levelRooms).c_str());
    if (m_selectedPosition == ROOMS) selY = middleY - 8;

    drawString (middleY - 7, middleX - 6, "Depth: ");
    if (m_status == WAITING) drawTile (middleY - 7, middleX - 6, 'D', Color (GREEN), Color (BLACK));
    drawString (middleY - 7, middleX + 2, formatNumber(m_levelDepth).c_str());
    if (m_selectedPosition == DEPTH) selY = middleY - 7;

    if (m_status != PROGRESS && m_selectedPosition != NONE) {
        drawString (selY, middleX + 1, "<", Color(RED), Color(BLACK));
        drawString (selY, middleX + 5, ">", Color(RED), Color(BLACK));
    }

    drawString (middleY - 5, middleX - 6, "Create: ");
    if (m_status == WAITING) drawTile (middleY - 5, middleX - 6, 'C', Color (GREEN), Color (BLACK));

    if (m_status == PROGRESS) {
        //drawString (middleY - 5, middleX + 3, ":");
        drawProgress (middleX + 2, middleY - 5, m_progress, m_levelDepth);
    } else if (m_status == COMPLETED) {
        drawString (middleY - 5, middleX + 2, "Done!");
        drawString (middleY - 4, middleX - 6, "Play");
        drawTile (middleY - 4, middleX - 6, 'P', Color(GREEN), Color(BLACK));
    }

    std::string explanation ("Use '+' and '-' to change values");
    int offset = getWidth()/2 - explanation.length()/2;
    drawString (getHeight()-2, offset, explanation.c_str());
}

void GeneratorWindow::update () {
    if (getArgs() && m_status == WAITING) {
        startGenerating();
        startPlaying();
        return;
    }
}

void GeneratorWindow::keyDown (unsigned char key) {
    Window::keyDown(key);

    if (m_status == PROGRESS) return; // Don't allow updates during generating

    if (m_status == COMPLETED && (key == 'p' || key == 'P')) {
        startPlaying();
        return; // Don't allow other actions
    }
    if (key == 'W' || key == 'w') m_selectedPosition = WIDTH;
    if (key == 'H' || key == 'h') m_selectedPosition = HEIGHT;
    if (key == 'R' || key == 'r') m_selectedPosition = ROOMS;
    if (key == 'D' || key == 'd') m_selectedPosition = DEPTH;

    if (key == 'C' || key == 'c') {
        startGenerating();
    }

    int adjustment = 0;
    if (key == KEY_RIGHT) adjustment = 1;
    if (key == KEY_LEFT) adjustment = -1;
    if (adjustment) {
        switch (m_selectedPosition) {
            case WIDTH: m_levelWidth    += adjustment; break;
            case HEIGHT: m_levelHeight  += adjustment; break;
            case ROOMS: m_levelRooms    += adjustment; break;
            case DEPTH: m_levelDepth    += adjustment; break;
            default:break;
        }
    }
    if (key == KEY_DOWN) {
        if (m_selectedPosition == WIDTH) m_selectedPosition = HEIGHT;
        else if (m_selectedPosition == HEIGHT) m_selectedPosition = ROOMS;
        else if (m_selectedPosition == ROOMS) m_selectedPosition = DEPTH;
        else if (m_selectedPosition == DEPTH) m_selectedPosition = WIDTH;
    }
    if (key == KEY_UP) {
        if (m_selectedPosition == WIDTH) m_selectedPosition = DEPTH;
        else if (m_selectedPosition == HEIGHT) m_selectedPosition = WIDTH;
        else if (m_selectedPosition == ROOMS) m_selectedPosition = HEIGHT;
        else if (m_selectedPosition == DEPTH) m_selectedPosition = ROOMS;
    }
}

void GeneratorWindow::startGenerating () {
    m_progress = 1;
    m_status = PROGRESS;

    unsigned int startArea = getEngine()->state()->map()->createArea (
            m_levelWidth,
            m_levelHeight,
            1);

    RuralGenerator rural;
    rural.initialise (getEngine());
    rural.mapHeight()   = m_levelHeight;
    rural.mapWidth()    = m_levelWidth;
    rural.area()        = startArea;
    rural.generate();

    for (EntityId stair : rural.getAreaLinks())
    {
        int retries = 0;
        bool success = false;
        unsigned int area =
            getEngine()->state()->map()->createArea (   m_levelWidth,
                    m_levelHeight,
                    m_levelDepth);

        LOG(INFO) << "Generating area: " << area << std::endl;
        DungeonGenerator l_generator;
        l_generator.initialise (getEngine());
        l_generator.maxDepth()      = m_levelDepth;
        l_generator.mapHeight()     = m_levelHeight;
        l_generator.mapWidth()      = m_levelWidth;
        l_generator.area()          = area;
        l_generator.numberOfRooms() = m_levelRooms;
        l_generator.downStairTarget() = 0;
        l_generator.upStairTarget() = stair;
        if (area == 2) {
            l_generator.createBoss() = true;
        }
        do {
            success = l_generator.generate();
        } while (!success && retries++ < 20);
        if (!success) {
            LOG(ERROR) << "Failed to generate a valid map" << std::endl;
        }
        getEngine()->state()->components()->get<StairComponent>(stair)->target =
            l_generator.upStairLink();
    }
    LOG(INFO) << "Placed "
        << getEngine()->state()->entityManager()->getMaxId()
        << " entities!"
        << std::endl;

    getEngine()->state()->map()->setArea (startArea);
    m_status = COMPLETED;
}

void GeneratorWindow::generateLevel () {

}

void GeneratorWindow::startPlaying() {
    MapWindow* l_win = new MapWindow();
    l_win->initialise (getEngine());
    getEngine()->getWindows()->replaceAllWindows (l_win);
}

