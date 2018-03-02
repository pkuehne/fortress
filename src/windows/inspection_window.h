#ifndef INSPECTION_WINDOW_H
#define INSPECTION_WINDOW_H

#include "window.h"
#include "../components/description_component.h"

class InspectionWindow : public Window {
public:
    void setup();
    void registerWidgets();

    void redraw();
    
    void gainFocus();
    void loseFocus();
private:
    DescriptionComponent*   m_description;
    std::vector<std::string>    m_lines;
    unsigned int                m_height;
    unsigned int                m_width;
};

#endif
