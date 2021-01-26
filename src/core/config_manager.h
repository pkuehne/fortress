#pragma once

#include <string>

class ConfigManager {
public:
    explicit ConfigManager(const std::string& filename);

    bool fullscreen;
    int windowWidth;
    int windowHeight;
    std::string tileset;
    int tileset_rows;
    int tileset_cols;
    std::string fontset;
    int fontset_rows;
    int fontset_cols;
    unsigned int tileHeight;
    unsigned int tileWidth;
};
