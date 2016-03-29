#include "selection_window.h"
#include "game_engine.h"
#include "description_component.h"
#include "inspection_window.h"

void SelectionWindow::resize()
{

}

void SelectionWindow::gainFocus()
{
    EntityHolder* l_entities = static_cast<EntityHolder*>(getArgs());
    if (!l_entities) return;

    for (EntityId entity: *l_entities) {
        DescriptionComponent* desc = getEngine()->getComponents()->get<DescriptionComponent>(entity);
        if (desc == nullptr) continue;

        m_entities.push_back(entity);
        m_lines.push_back (desc->title);
    }
    setDimensions (0, 0, 20, m_entities.size() + 5);
}

void SelectionWindow::redraw ()
{
    int yOffset = 2;
    for (std::string text: m_lines) {
        drawString (yOffset++, 2, text.c_str());
    }
    drawString (m_selection+2, 1, ">", Color(RED));

    drawString (yOffset+1, 1, "<Enter> to select");
    drawString (yOffset+1, 1, "<", Color(GREEN));
    drawString (yOffset+1, 7, ">", Color(GREEN));
}

void SelectionWindow::keyDown(unsigned char key)
{
    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
    }
    if (key == KEY_ENTER) {
        EntityId* l_target = new EntityId (m_entities[m_selection]);
        InspectionWindow* l_win = new InspectionWindow();
        l_win->initialise(getEngine(), l_target);
        getEngine()->getWindows()->replaceWindow (l_win);
        return;
    }
    if (key == KEY_UP) {
        if (m_selection > 0) m_selection--;
    }
    if (key == KEY_DOWN) {
        if (m_selection < m_lines.size()-1) m_selection++;
    }
}
