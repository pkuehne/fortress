#pragma once

#include <yaml-cpp/yaml.h>

class GameState;

class FileSaver {
public:
    FileSaver(GameState* state) : m_state(state) {}
    ~FileSaver() {}

    void saveState(const std::string& filename);
    void encodeMap(YAML::Node& node);

private:
    GameState* m_state = nullptr;
};
