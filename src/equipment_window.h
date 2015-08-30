#ifndef EQUIPMENT_WINDOW
#define EQUIPMENT_WINDOW

#include "window.h"

class EquipmentWindow : public Window {
public:
    virtual void gainFocus ();
    virtual void resize();
    virtual void redraw();
    virtual void keyDown (unsigned char key);

};

#endif
