#ifndef __GAME_ENGINE_INTERFACE_H__
#define __GAME_ENGINE_INTERFACE_H__

#include <string>
#include "window_manager.h"

class Window;
class EntityManager;
class Event;

class GameEngineInterface
{
public:
    GameEngineInterface () { }
    virtual ~GameEngineInterface () { }

    virtual void initialise (void)  = 0;
    virtual void tick (void)        = 0;
    virtual void start (void)       = 0;

    virtual bool& isPaused()        = 0;

    virtual void raiseEvent (Event* event)  = 0;
    virtual EntityManager& getEntities()    = 0;

    virtual void loadMap (const std::string& mapName) = 0;

    virtual unsigned long long getTick()    = 0;
    virtual WindowManager& getWindows()     = 0;
    virtual Window* getCurrentWindow()      = 0;

};

#endif
