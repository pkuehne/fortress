#ifndef __GAME_ENGINE_INTERFACE_H__
#define __GAME_ENGINE_INTERFACE_H__

#include <string>
//#include "window_manager_interface.h"
#include "entity_manager.h"
#include "graphics_interface.h"

//class WindowManager;
class Event;
class WindowManagerInterface;

class GameEngineInterface
{
public:
    GameEngineInterface () { }
    virtual ~GameEngineInterface () { }

    virtual void initialise (void)  = 0;
    virtual void tick (void)        = 0;

    virtual bool& isPaused()        = 0;

    virtual void raiseEvent (Event* event)  = 0;
    virtual EntityManager& getEntities()    = 0;

    virtual void loadMap (const std::string& mapName) = 0;

    virtual unsigned long long getTick()    = 0;
    virtual WindowManagerInterface* getWindows()     = 0;

    virtual GraphicsInterface* getGraphics() = 0;

};

#endif
