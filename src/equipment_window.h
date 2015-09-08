#ifndef EQUIPMENT_WINDOW
#define EQUIPMENT_WINDOW

#include "window.h"
#include "entity.h"

class EquipmentWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

private:
    EntityId    m_selectedItem;
    int         m_selectedPage;
};

#endif
