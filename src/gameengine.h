#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "map.h"
#include "screen.h"
#include "unitlist.h"
#include <string>

class GameEngine {
public:
    static GameEngine* getEngine ();

    const Map& getMap() { return m_map; }
    void generateMap (int seed = 0);
    void loadMap (const std::string& mapName);

    Screen& getScreen() { return m_screen; } 

    UnitList& getUnits() { return m_units; }

    bool& isDefender() { return m_isDefender; }
    void start (void);
    void tick (void);

private:
    GameEngine ();
    ~GameEngine ();
    static GameEngine*  s_engine;

    void checkVictoryConditions();
    void updateUnitPath ();
    void checkUnitSurroundings();
    void updateFights ();

private:
    Screen      m_screen;
    Map         m_map;
    UnitList    m_units;
    bool        m_isDefender;
    unsigned long long  m_tick;
};

#endif
