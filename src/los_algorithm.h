#ifndef LOS_ALGORITHM
#define LOS_ALGORITHM

#include "game_engine_interface.h"
#include "utility.h"

class LosAlgorithm {
public:
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    bool hasLos (const Location& start, const Location& end);

private:
    bool viewBlocked (const Location&);
    
private:
    GameEngineInterface*    m_engine;
};

#endif
