#pragma once

#include "widget.h"
#include <vector>

class ListBox : public Widget {
    public:
        ListBox() {}

        virtual void render();
        virtual void keyPress(unsigned char key);

        std::vector<std::string> items;
        unsigned int selectedItem = 0;

    private:
        unsigned int m_topOffset = 0;
        unsigned int m_selectionPos = 0;
};
