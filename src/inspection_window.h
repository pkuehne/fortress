#ifndef INSPECTION_WINDOW_H
#define INSPECTION_WINDOW_H

#include "window.h"
#include "description_component.h"

class InspectionWindow : public Window {
public:
    void keyDown (unsigned char key);
    void redraw();
    void resize();

    void gainFocus();
    void loseFocus();
private:
    DescriptionComponent*   m_description;
};

#endif