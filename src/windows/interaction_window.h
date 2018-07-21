#pragma once

#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/openable_component.h"
#include "window.h"

class ListBox;

typedef struct {
    EntityHolder entities;
} InteractionWindowArgs;

typedef struct {
    DescriptionComponent* desc;
    OpenableComponent* open;
    DroppableComponent* drop;
} ComponentStore;

class InteractionWindow : public Window {
public:
    void setArguments(std::shared_ptr<InteractionWindowArgs> args) {
        m_arguments = args;
    }
    void setup();
    void registerWidgets();
    void nextTurn();

private:
    void listSelection(ListBox* box);
    void updateScreen();

private:
    std::shared_ptr<InteractionWindowArgs> m_arguments;
    std::vector<EntityId> m_entities;
    std::vector<ComponentStore> m_components;
};
