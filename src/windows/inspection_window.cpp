#include "inspection_window.h"
#include "game_engine.h"
#include "description_component.h"

void InspectionWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }
}

void InspectionWindow::resize()
{
    setDimensions (0, 0, m_width, m_height+5);
}

void InspectionWindow::redraw()
{
    if (!m_description) return;
    unsigned int yPos = 2;
    for (std::string line : m_lines) {
        drawString (yPos++,  2, line.c_str());
    }
}

void InspectionWindow::gainFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (!l_entity) return;

    m_description = getEngine()->getComponents()->get<DescriptionComponent>(*l_entity);
    if (!m_description) return;

    setTitle (m_description->title);
    m_width = 30;
    m_height = wrapText (m_description->text, m_lines, m_width, 10);
}

void InspectionWindow::loseFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) delete l_entity;
}
