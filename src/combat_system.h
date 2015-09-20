#include "game_system_base.h"
#include "utility.h"

class CombatSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);

private:
    void updateLog (const EntityId& attacker, const EntityId& target, int damage);
};