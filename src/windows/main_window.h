#pragma once

#include "main_window.h"
#include "window.h"

class MainWindow : public Window {
public:
    void setup() override;
    void registerWidgets() override;
};
