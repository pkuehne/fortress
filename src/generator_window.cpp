#include "generator_window.h"
#include "game_engine.h"
#include <sstream>

std::string GeneratorWindow::formatNumber (int number) {
    std::stringstream str;

    if (number < 10) str << " ";
    if (number < 100) str << " ";
    str << number;
    return str.str();
}

void GeneratorWindow::gainFocus () {
    setTitle (" Create New World ");
    m_levelWidth = 50;
    m_levelHeight = 50;
    m_levelRooms = 10;
    m_worldSize = 129;
    m_selectedPosition = NONE;
}

void GeneratorWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
}

void GeneratorWindow::redraw() {

    int middleX = getWidth()/2;
    int middleY = getHeight();
    int selY    = 0;

    drawString (middleY - 11, middleX - 10, "Level Parameters:");
    drawString (middleY - 10, middleX - 6, "Width: ");
    drawTile (middleY - 10, middleX - 6, 'W', Color (GREEN), Color (BLACK));
        drawString (middleY - 10, middleX + 2, formatNumber(m_levelWidth).c_str());
        if (m_selectedPosition == WIDTH) selY = middleY - 10;
    drawString (middleY - 9, middleX - 6, "Height: ");
    drawTile (middleY - 9, middleX - 6, 'H', Color (GREEN), Color (BLACK));
        drawString (middleY - 9, middleX + 2, formatNumber(m_levelHeight).c_str());
        if (m_selectedPosition == HEIGHT) selY = middleY - 9;

    drawString (middleY - 8, middleX - 6, "Rooms: ");
    drawTile (middleY - 8, middleX - 6, 'R', Color (GREEN), Color (BLACK));
        drawString (middleY - 8, middleX + 2, formatNumber(m_levelRooms).c_str());
        if (m_selectedPosition == ROOMS) selY = middleY - 8;

    if (m_selectedPosition != NONE) {
        drawTile (selY, middleX + 1, '<', Color(RED), Color(BLACK));
        drawTile (selY, middleX + 5, '>', Color(RED), Color(BLACK));
    }

    drawString (middleY - 6, middleX - 3, "Create!");
    drawTile (middleY - 6, middleX - 3, 'C', Color (GREEN), Color (BLACK));


    std::string explanation ("Use '+' and '-' to change values");
    int offset = getWidth()/2 - explanation.length()/2;
    drawString (getHeight()-2, offset, explanation.c_str());
}

void GeneratorWindow::keyDown (unsigned char key) {
    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }

    if (key == 'W' || key == 'w') m_selectedPosition = WIDTH;
    if (key == 'H' || key == 'h') m_selectedPosition = HEIGHT;
    if (key == 'R' || key == 'r') m_selectedPosition = ROOMS;

    if (key == 'C' || key == 'c') {
        std::cout << "Creating" << std::endl;
    }

    int adjustment = 0;
    if (key == '+') adjustment = 1;
    if (key == '-') adjustment = -1;
    switch (m_selectedPosition) {
        case WIDTH: m_levelWidth += adjustment; break;
        case HEIGHT: m_levelHeight += adjustment; break;
        case ROOMS: m_levelRooms += adjustment; break;
        default:break;
    }
}
