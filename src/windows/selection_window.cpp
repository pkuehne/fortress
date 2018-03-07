#include "selection_window.h"
#include "../core/game_engine.h"
#include "../components/description_component.h"
#include "inspection_window.h"
#include "listbox.h"

void SelectionWindow::setup()
{
    setEntities(static_cast<EntityHolder *>(getArgs()));

    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    setWidth(20);
    setHeight(m_entities.size() + 4);
    
}

void SelectionWindow::registerWidgets()
{
    ListBox *box = this->createWidget<ListBox>("lstEntities", 2, 2);

    for (std::string line : m_lines)
    {
        box->items.push_back(line);
    }

    box->setHeight(m_lines.size());
    box->onItemSelected = [](ListBox *box) {
        SelectionWindow *win = dynamic_cast<SelectionWindow *>(box->getWindow());
        EntityId *l_target = new EntityId(win->getEntities()[box->getSelectedItem()]);
        win->getEngine()->getWindows()->createWindow<InspectionWindow>(l_target);
    };
}

void SelectionWindow::setEntities(EntityHolder* entities)
{
    if (!entities)
        return;

    for (EntityId entity : *entities)
    {
        DescriptionComponent *desc = getEngine()->state()->components()->get<DescriptionComponent>(entity);
        if (desc == nullptr)
            continue;

        m_entities.push_back(entity);
        m_lines.push_back(desc->title);
    }
}