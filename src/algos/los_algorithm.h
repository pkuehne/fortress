#pragma once

class Location;
class GameEngine;

class LosAlgorithm {
public:
    LosAlgorithm() {}
    ~LosAlgorithm() {}
    void initialise(GameEngine* engine) { m_engine = engine; }
    bool hasLos(const Location& start, const Location& end);

private:
    bool viewBlocked(const Location&);

private:
    GameEngine* m_engine = nullptr;
};
