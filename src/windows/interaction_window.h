#pragma once

#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/npc_component.h"
#include "../components/openable_component.h"
#include "window.h"

class ListBox;

typedef struct {
    DescriptionComponent* desc;
    OpenableComponent* open;
    DroppableComponent* drop;
    NpcComponent* npc;
} ComponentStore;

class InteractionWindow : public Window {
public:
    explicit InteractionWindow(EntityHolder& entities)
        : m_inputEntities(entities) {}
    void setup();
    void registerWidgets();
    void nextTurn();

private:
    void listSelection(ListBox* box);
    void updateScreen();

private:
    std::vector<EntityId> m_entities;
    std::vector<ComponentStore> m_components;
    EntityHolder m_inputEntities;
};
