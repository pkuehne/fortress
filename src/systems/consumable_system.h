#include "../core/game_system_base.h"
#include "../core/utility.h"

class ConsumableSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
};
