#include "selection_window.h"
#include "game_engine.h"
#include "description_component.h"

void SelectionWindow::resize()
{

}

void SelectionWindow::gainFocus()
{
	EntityHolder* l_entities = static_cast<EntityHolder*>(getArgs());
	if (!l_entities) return;

	for (EntityId entity: *l_entities) {
		DescriptionComponent* desc = getEngine()->getComponents()->get<DescriptionComponent>(entity);
		if (!desc) continue;

		m_entities.push_back(entity);
		m_lines.push_back (desc->title);
	}
    setDimensions (0, 0, 20, m_entities.size() + 5);
}

void SelectionWindow::redraw ()
{
	int yOffset = 2;
	for (std::string text: m_lines) {
		drawString (yOffset++, 3, text.c_str(), Color(WHITE), Color(BLACK));
	}
}

void SelectionWindow::keyDown(unsigned char key)
{
    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
