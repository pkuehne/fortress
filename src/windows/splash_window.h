#pragma once

#include "window.h"

class SplashWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();
    virtual void keyPress(unsigned char key);
};
