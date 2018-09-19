#pragma once

#include "window.h"

class DialogWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void nextTurn();
    void destroy();
};
