#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "map.h"

class GameEngine {
public:
    static GameEngine* getEngine ();
    const Map& getMap() { return m_map; }
    void generateMap (int seed = 0);

private:
    GameEngine ();
    ~GameEngine ();
    static GameEngine*  s_engine;

private:
    Map     m_map;
};

#endif
