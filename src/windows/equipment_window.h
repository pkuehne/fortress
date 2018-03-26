#ifndef EQUIPMENT_WINDOW
#define EQUIPMENT_WINDOW

#include "window.h"
#include "../core/entity.h"

class EquipmentWindow : public Window {
    public:
        virtual void setup ();
        virtual void registerWidgets();

        void setSelectedItem(EntityId item);
        EntityId getSelectedItem() { return m_selectedItem; }
        bool itemSelected() { return m_selectedItem != 0; }
        void updateItemNames();
    private:
        EntityId    m_selectedItem;
        std::vector<EntityId> m_rucksackEntities;
};

#endif
