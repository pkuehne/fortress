#ifndef EQUIPMENT_WINDOW
#define EQUIPMENT_WINDOW

#include "window.h"
#include "../core/entity.h"

class EquipmentWindow : public Window {
    public:
        virtual void setup ();
        virtual void registerWidgets();
        virtual void keyPress (unsigned char key);

        void setSelectedItem(EntityId item) { m_selectedItem = item; }
        EntityId getSelectedItem() { return m_selectedItem; }
        bool itemSelected() { return m_selectedItem != 0; }
        void updateItemNames();
    private:
        EntityId    m_selectedItem;
};

#endif
