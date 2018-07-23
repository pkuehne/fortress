#pragma once

#include "window.h"

class LoadWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void loadFiles();

private:
    void loadState(const std::string& filename);
};
