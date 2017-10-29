#pragma once

#include <window.h>

class QuestWindow : public Window {
    public:
        void registerWidgets();
        void resize();
        void keyPress(unsigned char key);
};
