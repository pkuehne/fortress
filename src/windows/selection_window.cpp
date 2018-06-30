#include "selection_window.h"
#include "../components/description_component.h"
#include "../core/game_engine.h"
#include "inspection_window.h"
#include "listbox.h"

void SelectionWindow::setup() {
    setEntities(m_arguments->entities);

    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    setWidth(20);
    setHeight(m_entities.size() + 4);
}

void SelectionWindow::registerWidgets() {
    ListBox* box = this->createWidget<ListBox>("lstEntities", 1, 1);

    for (std::string line : m_lines) {
        ListBoxItem item;
        item.setText(line);
        box->addItem(item);
    }

    box->setHeight(m_lines.size());
    box->setItemSelectedCallback([&](ListBox* box) {
        EntityId target = m_entities[box->getSelection()];
        m_arguments->selectionCallback(getEngine(), target);
    });
}

void SelectionWindow::setEntities(EntityHolder& entities) {
    for (EntityId entity : entities) {
        DescriptionComponent* desc =
            getEngine()->state()->components()->get<DescriptionComponent>(
                entity);
        if (desc == nullptr)
            continue;

        m_entities.push_back(entity);
        m_lines.push_back(desc->title);
    }
}