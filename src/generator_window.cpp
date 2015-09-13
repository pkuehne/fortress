#include "generator_window.h"
#include "game_engine.h"
#include <sstream>

void GeneratorWindow::gainFocus () {
    setTitle (" Create New World ");
    m_levelWidth = 50;
    m_levelHeight = 50;
    m_levelRooms = 10;
    m_worldSize = 129;
}

void GeneratorWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
}

void GeneratorWindow::redraw() {

    int middleX = getWidth()/2;
    int middleY = getHeight();

    std::stringstream width; width << m_levelWidth;
    std::stringstream height; height << m_levelHeight;
    std::stringstream rooms; rooms << m_levelRooms;

    drawString (middleY - 11, middleX - 10, "Level Parameters:");
    drawString (middleY - 10, middleX - 6, "Width: ");
    drawTile (middleY - 10, middleX - 6, 'W', Color (GREEN), Color (BLACK));
        drawString (middleY - 10, middleX + 2, width.str().c_str());
    drawString (middleY - 9, middleX - 6, "Height: ");
    drawTile (middleY - 9, middleX - 6, 'H', Color (GREEN), Color (BLACK));
        drawString (middleY - 9, middleX + 2, width.str().c_str());

    drawString (middleY - 8, middleX - 6, "Rooms: ");
    drawTile (middleY - 8, middleX - 6, 'R', Color (GREEN), Color (BLACK));
        drawString (middleY - 8, middleX + 2, rooms.str().c_str());

    drawString (middleY - 6, middleX - 3, "Create!");
    drawTile (middleY - 6, middleX - 3, 'C', Color (GREEN), Color (BLACK));

    std::string explanation ("Use <Up> and <Down> to change values");
    int offset = getWidth()/2 - explanation.length()/2;
    drawString (getHeight()-2, offset, explanation.c_str());
}

void GeneratorWindow::keyDown (unsigned char key) {
    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
