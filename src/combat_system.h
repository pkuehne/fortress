#include "game_system_base.h"
#include "utility.h"

class CombatSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);

private:
    bool checkForEnemies (DIRECTION dir);
};
