#include "inspection_window.h"
#include "game_engine.h"
#include "description_component.h"

void InspectionWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }
}

void InspectionWindow::resize() {
    int width = 30;
    int height = 7;

    setDimensions (0, 0, width, height);
}

void InspectionWindow::redraw()
{
    if (!m_description) return;
    drawString (3,  2, m_description->text.c_str());
}

void InspectionWindow::gainFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (!l_entity) return;

    m_description = getEngine()->getComponents()->get<DescriptionComponent>(*l_entity);
    if (!m_description) return;

    setTitle (m_description->title);
}

void InspectionWindow::loseFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) delete l_entity;
}
