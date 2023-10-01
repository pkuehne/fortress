#pragma once

#include <functional>
#include <yaml-cpp/yaml.h>

class EntityManager;
class MapManager;
class ComponentManager;

typedef std::function<void(unsigned int current, unsigned int max,
                           const std::string& status)>
    StatusCallback;

class FileLoader {
public:
    explicit FileLoader(std::shared_ptr<MapManager> map,
                        std::shared_ptr<EntityManager> entities,
                        std::shared_ptr<ComponentManager> components)
        : m_map(map), m_entities(entities), m_components(components) {}

    ~FileLoader() = default;

    void setStatusCallback(StatusCallback cb) { m_cb = cb; }
    void updateStatus(const std::string& status);

    void loadState(const std::string& filename);
    void decodeEntities(const YAML::Node& node);

private:
    std::shared_ptr<MapManager> m_map = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;

    StatusCallback m_cb = [](unsigned int current, unsigned int max,
                             const std::string& status) {};
    unsigned int m_totalSteps = 0;
    unsigned int m_currentStep = 0;
};
