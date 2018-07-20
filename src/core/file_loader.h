#pragma once

#include <yaml-cpp/yaml.h>

class GameState;

typedef std::function<void(unsigned int current, unsigned int max,
                           const std::string& status)>
    StatusCallback;

class FileLoader {
public:
    explicit FileLoader(GameState* state) { m_state = state; }
    ~FileLoader() = default;

    void setStatusCallback(StatusCallback cb) { m_cb = cb; }
    void updateStatus(const std::string& status);

    void loadState(const std::string& filename);

private:
    GameState* m_state = nullptr;
    StatusCallback m_cb = [](unsigned int current, unsigned int max,
                             const std::string& status) {};
    unsigned int m_totalSteps = 0;
    unsigned int m_currentStep = 0;
};
