#include "listbox.h"
#include "../core/color.h"
#include "../core/utility.h"
#include <iostream>

void ListBox::render()
{
    for (unsigned int ii = 0; ii < this->getHeight(); ii++) {
        if (ii >= items.size()) {
            break;
        }
        if (m_selectedItem-m_topOffset == ii) {
            this->drawString(0, ii, ">", COLOR(RED));
        }

        this->drawString(1, ii, items[ii+m_topOffset].c_str());
    }
}

void ListBox::keyPress(unsigned char key)
{
    if (key == '+') {
        m_selectedItem = (m_selectedItem == items.size()-1) ? items.size()-1: m_selectedItem+1;
        if (m_selectedItem >= this->getHeight()) {
            m_topOffset = m_selectedItem - this->getHeight() + 1;
        }
    }
    if (key == '-') {
        m_selectedItem = (m_selectedItem == 0) ? 0 : m_selectedItem-1;
        if (m_selectedItem < m_topOffset) {
            m_topOffset = 0;
        }
    }
    if (key == KEY_ENTER && onItemSelected) {
        onItemSelected(this);
    }
}
