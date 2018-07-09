#pragma once

#include "window.h"

class SaveWindow : public Window {
public:
    void setup();
    void registerWidgets();

private:
    void saveState(const std::string& filename);
};
