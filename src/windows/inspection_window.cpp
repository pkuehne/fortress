#include "inspection_window.h"
#include "../core/game_engine.h"
#include "../components/description_component.h"

void InspectionWindow::setup()
{
    setTitle(m_description->title);
    setDimensions(0, 0, m_width, m_height + 5);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void InspectionWindow::registerWidgets()
{

}

void InspectionWindow::redraw()
{
    if (!m_description)
        return;
    unsigned int yOffset = 2;
    for (std::string line : m_lines)
    {
        drawString(yOffset++, 2, line.c_str());
    }
}

void InspectionWindow::gainFocus()
{
    EntityId *l_entity = static_cast<EntityId *>(getArgs());
    if (!l_entity)
        return;

    m_description = getEngine()->state()->components()->get<DescriptionComponent>(*l_entity);
    if (!m_description)
        return;

    m_width = 30;
    m_height = wrapText(m_description->text, m_lines, m_width, 10);
}

void InspectionWindow::loseFocus()
{
    EntityId *l_entity = static_cast<EntityId *>(getArgs());
    if (l_entity)
        delete l_entity;
}
