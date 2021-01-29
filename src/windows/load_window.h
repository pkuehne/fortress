#pragma once

#include "window.h"

class LoadWindow : public Window {
public:
    void setup() override;
    void registerWidgets() override;
    void loadFiles();

private:
    void loadState(const std::string& filename);
};
