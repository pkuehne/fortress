#ifndef __GAME_ENGINE_INTERFACE_H__
#define __GAME_ENGINE_INTERFACE_H__

#include <string>
//#include "window_manager_interface.h"
#include "entity_manager_interface.h"
#include "graphics_interface.h"
#include "tile.h"

//class WindowManager;
class Event;
class WindowManagerInterface;
class GameSystemInterface;

typedef enum {
    INFO    = 0,
    GOOD    = 1,
    WARN    = 2,
    CRIT    = 3
} MessageType;

typedef struct {
    MessageType severity;
    std::string message;
} Message;

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
    
    virtual void raiseEvent (Event* event)  = 0;
    virtual EntityManagerInterface* getEntities()    = 0;

    virtual void loadMap (unsigned int width, unsigned int height) = 0;

    virtual unsigned long long getTick()    = 0;
    virtual WindowManagerInterface* getWindows()     = 0;

    virtual GraphicsInterface* getGraphics() = 0;

    virtual void addSystem (GameSystemInterface* a_system) = 0;

    virtual void addMessage (const Message& message) = 0;
    virtual void addMessage (const MessageType&, const std::string& message) = 0 ;
    virtual std::vector<Message>& getMessages() = 0;

    virtual void setLevel (unsigned int level) = 0;
    virtual unsigned int getLevel () = 0;

    virtual void setMaxLevel (unsigned int level) = 0;
    virtual unsigned int getMaxLevel () = 0;

    virtual Tile& getTile (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual Tile& getTile (const Location& location) = 0;
    virtual Tile& getTile (unsigned int index) = 0;

    virtual int map2index (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual void index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z) = 0;
    virtual bool isValidTile (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual bool isValidTile (unsigned int index) = 0;

    virtual unsigned int getMapHeight() = 0;
    virtual unsigned int getMapWidth() = 0;

};

#endif
