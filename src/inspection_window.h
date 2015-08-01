#ifndef INSPECTION_WINDOW_H
#define INSPECTION_WINDOW_H

#include "window.h"

class InspectionWindow : public Window {
public:
    void keyDown (unsigned char key);
    void beforeRedraw(){ }

    void gainFocus();
    void loseFocus();
};

#endif
