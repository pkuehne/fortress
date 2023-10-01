#pragma once
#include <memory>

class Location;
class MapManager;

class LosAlgorithm {
public:
    LosAlgorithm() {}
    ~LosAlgorithm() {}
    void initialise(std::shared_ptr<MapManager> map) { m_map = map; }
    bool hasLos(const Location& start, const Location& end);

private:
    bool viewBlocked(const Location&);

private:
    std::shared_ptr<MapManager> m_map;
};
