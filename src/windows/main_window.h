#pragma once

#include "main_window.h"
#include "window.h"

class MainWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();
};
