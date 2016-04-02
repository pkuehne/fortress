#include "game_system_base.h"

class HealthSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
    virtual void update () override;
};
