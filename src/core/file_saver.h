#pragma once

#include <yaml-cpp/yaml.h>

class GameState;

typedef std::function<void(unsigned int current, unsigned int max,
                           const std::string& status)>
    StatusCallback;

class FileSaver {
public:
    explicit FileSaver(GameState* state) : m_state(state) {}
    ~FileSaver() = default;

    void setStatusCallback(StatusCallback cb) { m_cb = cb; }
    void updateStatus(const std::string& status);
    void saveState(const std::string& filename);
    void encodeMap(YAML::Node& node);
    void encodeArea(YAML::Node& node, unsigned int area);
    void encodeAreaZero(YAML::Node& node);
    void encodeEntities(YAML::Node& node, unsigned int area);

private:
    GameState* m_state = nullptr;
    StatusCallback m_cb = [](unsigned int current, unsigned int max,
                             const std::string& status) {};
    unsigned int m_totalSteps = 0;
    unsigned int m_currentStep = 0;
};
