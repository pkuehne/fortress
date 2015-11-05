#include "game_system_base.h"
#include "utility.h"

class ConsumableSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
};
