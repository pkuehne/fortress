#ifndef LOS_ALGORITHM
#define LOS_ALGORITHM

class Location;
class GameEngine;

class LosAlgorithm {
public:
    void initialise(GameEngine* engine) { m_engine = engine; }
    bool hasLos(const Location& start, const Location& end);

private:
    bool viewBlocked(const Location&);

private:
    GameEngine* m_engine;
};

#endif
