#ifndef INSPECTION_WINDOW_H
#define INSPECTION_WINDOW_H

#include "../components/description_component.h"
#include "window.h"

class InspectionWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void destroy();

private:
};

#endif
