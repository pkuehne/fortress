#include "listbox.h"
#include "../core/color.h"
#include "../core/utility.h"
#include <iostream>

void ListBox::render() {
    unsigned int itemLeftOffset = getSensitive() ? 1 : 0;

    for (unsigned int ii = 0; ii < this->getHeight(); ii++) {
        if (ii >= m_items.size()) {
            break;
        }
        if (m_selection - m_topOffset == ii && getSensitive()) {
            this->drawString(0, ii, ">", COLOR(RED));
        }
        ListBoxItem& item = m_items[ii + m_topOffset];
        this->drawString(itemLeftOffset, ii, item.getText().c_str(),
                         item.getColor());
    }
}

void ListBox::keyPress(unsigned char key) {
    if (key == '+' || key == KEY_DOWN) {
        m_selection = (m_selection == m_items.size() - 1) ? m_items.size() - 1
                                                          : m_selection + 1;
    }
    if (key == '-' || key == KEY_UP) {
        m_selection = (m_selection == 0) ? 0 : m_selection - 1;
    }

    updateTopOffset();

    if (key == KEY_ENTER && m_itemSelectedCb) {
        m_itemSelectedCb(this);
    }
}

void ListBox::updateTopOffset() {
    if (m_selection >= this->getHeight()) {
        m_topOffset = m_selection - this->getHeight() + 1;
    }
    if (m_selection <= m_topOffset) {
        m_topOffset = 0;
    }
}

void ListBox::scrollToBottom() { setSelection(m_items.size() - 1); }
