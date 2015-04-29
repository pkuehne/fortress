#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#include "event.h"

class BaseSystem {
public:
    virtual void handleEvent (const Event* event) { }
    virtual void update () { };

    virtual ~BaseSystem() { }
};

#endif
