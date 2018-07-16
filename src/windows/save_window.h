#pragma once

#include "window.h"

class SaveWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void loadFiles();

private:
    void saveState(const std::string& filename);
};
