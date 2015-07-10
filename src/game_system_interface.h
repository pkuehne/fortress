#ifndef GAME_SYSTEM_INTERFACE_H
#define GAME_SYSTEM_INTERFACE_H

#include "event.h"

class GameSystemInterface {
public:
    virtual void handleEvent (const Event* event) = 0;
    virtual void update () = 0;
    virtual ~GameSystemInterface() { }
};

#endif
