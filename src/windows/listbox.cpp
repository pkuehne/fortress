#include "listbox.h"
#include "../core/color.h"
#include <iostream>

void ListBox::render()
{
    for (unsigned int ii = 0; ii < this->height; ii++) {
        if (ii >= items.size()) {
            break;
        }
        if (selectedItem == ii) {
            this->drawString(0, ii, ">", COLOR(RED));
        }

        this->drawString(1, ii, items[ii].c_str());
    }
}

void ListBox::keyPress(unsigned char key)
{
    if (key == '+') {
        selectedItem = (selectedItem == items.size()-1) ? items.size()-1: selectedItem+1;
    }
    if (key == '-') {
        selectedItem = (selectedItem == 0) ? 0 : selectedItem-1;
        
    }
}
