#pragma once

#include "window.h"

class DialogWindow : public Window {
public:
    void setup() override;
    void registerWidgets() override;
    void nextTurn() override;
    void destroy() override;
};
