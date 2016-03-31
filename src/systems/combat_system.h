#include "game_system_base.h"
#include "utility.h"

class CombatSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
    void handleAttack (EntityId attacker, EntityId defender);

private:
    void updateLog (const EntityId& attacker, const EntityId& target, int damage);
};
