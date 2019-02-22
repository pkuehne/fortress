#pragma once
#include <memory>

class Location;
class MapManager;
class ComponentManager;

class LosAlgorithm {
public:
    LosAlgorithm() {}
    ~LosAlgorithm() {}
    void initialise(std::shared_ptr<MapManager> map,
                    std::shared_ptr<ComponentManager> components) {
        m_map = map;
        m_components = components;
    }
    bool hasLos(const Location& start, const Location& end);

private:
    bool viewBlocked(const Location&);

private:
    std::shared_ptr<MapManager> m_map;
    std::shared_ptr<ComponentManager> m_components;
};
