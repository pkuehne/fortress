#include "game_system_base.h"

class CombatSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);

private:
    bool checkForEnemies (MoveEntityEvent::DIRECTION dir);
};
