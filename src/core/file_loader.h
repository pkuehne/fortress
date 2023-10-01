#pragma once

#include <functional>
#include <yaml-cpp/yaml.h>

class EntityManager;
class MapManager;

typedef std::function<void(unsigned int current, unsigned int max,
                           const std::string& status)>
    StatusCallback;

class FileLoader {
public:
    explicit FileLoader(std::shared_ptr<MapManager> map,
                        std::shared_ptr<EntityManager> entities)
        : m_map(map), m_entities(entities) {}

    ~FileLoader() = default;

    void setStatusCallback(StatusCallback cb) { m_cb = cb; }
    void updateStatus(const std::string& status);

    void loadState(const std::string& filename);
    void decodeEntities(const YAML::Node& node);

private:
    std::shared_ptr<MapManager> m_map = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;

    StatusCallback m_cb = [](unsigned int current, unsigned int max,
                             const std::string& status) {};
    unsigned int m_totalSteps = 0;
    unsigned int m_currentStep = 0;
};
