#pragma once

#include "../core/entity.h"
#include "window.h"
#include <vector>

class Label;

class EquipmentWindow : public Window {
public:
    EquipmentWindow() {}
    ~EquipmentWindow() {}
    virtual void setup();
    virtual void registerWidgets();
    virtual void nextTurn();

    void setSelectedItem(EntityId item);
    EntityId getSelectedItem() { return m_selectedItem; }
    bool itemSelected() { return m_selectedItem != 0; }
    void updateItemNames();

private:
    void selectItem(Label* l);
    const char* nameOrNothing(EntityId item);

private:
    EntityId m_selectedItem = 0;
    std::vector<EntityId> m_rucksackEntities;
};
