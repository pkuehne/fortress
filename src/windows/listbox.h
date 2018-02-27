#pragma once

#include "widget.h"
#include <vector>

class ListBox : public Widget {
    public:
        ListBox() {}

        ListBox* setSelectedItem(unsigned int item) {
            m_selectedItem = item;
            return this;
        }
        unsigned int getSelectedItem() {
            return m_selectedItem;
        }
        virtual void render();
        virtual void keyPress(unsigned char key);

        std::vector<std::string> items;

        void(*onItemSelected)(ListBox*);

    private:
        unsigned int m_selectedItem = 0;

        unsigned int m_topOffset = 0;
        unsigned int m_selectionPos = 0;
};
