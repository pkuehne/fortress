#pragma once

#include "window.h"

class SaveWindow : public Window {
public:
    void setup() override;
    void registerWidgets() override;
    void loadFiles();

private:
    void saveState(const std::string& filename);
};
