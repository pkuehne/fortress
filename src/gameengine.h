#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "map.h"
#include "screen.h"
#include <string>

class GameEngine {
public:
    static GameEngine* getEngine ();
    const Map& getMap() { return m_map; }
    void generateMap (int seed = 0);

    void loadMap (const std::string& mapName);
    void execute ();

private:
    GameEngine ();
    ~GameEngine ();
    static GameEngine*  s_engine;

private:
    Screen  m_screen;
    Map     m_map;
};

#endif
