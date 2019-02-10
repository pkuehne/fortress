#include "config_manager.h"
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

ConfigManager::ConfigManager(const std::string& filename) {
    YAML::Node config;
    try {
        config = YAML::LoadFile(filename);
    } catch (const std::exception& e) {
        //
    }
    fullscreen = config["fullscreen"].as<bool>(true);
    windowWidth = config["WindowWidth"].as<int>(800);
    windowHeight = config["WindowHeight"].as<int>(600);
    tileset = config["Tileset"].as<std::string>("");
    tileset_rows = config["Tileset_Rows"].as<int>(16);
    tileset_cols = config["Tileset_Cols"].as<int>(16);
    fontset = config["Fontset"].as<std::string>("");
    fontset_rows = config["Fontset_Rows"].as<int>(16);
    fontset_cols = config["Fontset_Cols"].as<int>(16);
}
