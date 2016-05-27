#ifndef __GAME_ENGINE_INTERFACE_H__
#define __GAME_ENGINE_INTERFACE_H__

#include "entity.h"
#include "utility.h"
#include "tile.h"

#include <string>
#include <vector>
class Event;
class WindowManagerInterface;
class GameSystemInterface;
class EntityManagerInterface;
class GraphicsInterface;
class Location;
class GameState;

class GameEngineInterface
{
public:
    GameEngineInterface () { }
    virtual ~GameEngineInterface () { }

    virtual void initialise (void)  = 0;
    virtual void tick (void)        = 0;

    virtual void quit()             = 0;
    virtual bool isPlayerTurn()     = 0;
    virtual void swapTurn()         = 0;
    virtual unsigned int getTurn()  = 0;
    virtual void setTurn (unsigned int) = 0;
    virtual void raiseEvent (Event* event)  = 0;
    virtual GameState* state() = 0;

    virtual unsigned long long getTick()    = 0;
    virtual WindowManagerInterface* getWindows()     = 0;

    virtual GraphicsInterface* getGraphics() = 0;

    virtual void addSystem (GameSystemInterface* a_system) = 0;
};

#endif
