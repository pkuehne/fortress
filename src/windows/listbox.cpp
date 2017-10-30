#include "listbox.h"
#include "../core/color.h"
#include "../core/utility.h"
#include <iostream>

void ListBox::render()
{
    for (unsigned int ii = 0; ii < this->height; ii++) {
        if (ii >= items.size()) {
            break;
        }
        if (selectedItem-m_topOffset == ii) {
            this->drawString(0, ii, ">", COLOR(RED));
        }

        this->drawString(1, ii, items[ii+m_topOffset].c_str());
    }
}

void ListBox::keyPress(unsigned char key)
{
    if (key == '+') {
        selectedItem = (selectedItem == items.size()-1) ? items.size()-1: selectedItem+1;
        if (selectedItem >= this->height) {
            m_topOffset = selectedItem - this->height + 1;
        }
    }
    if (key == '-') {
        selectedItem = (selectedItem == 0) ? 0 : selectedItem-1;
        if (selectedItem < m_topOffset) {
            m_topOffset = 0;
        }
    }
    if (key == KEY_ENTER && onItemSelected) {
        onItemSelected(this);
    }
}
