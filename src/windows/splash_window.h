#pragma once

#include "window.h"

class SplashWindow : public Window {
public:
    void setup() override;
    void registerWidgets() override;
    void keyPress(unsigned char key) override;
};
