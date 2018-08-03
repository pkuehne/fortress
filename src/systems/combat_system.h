#pragma once

#include "../core/game_system_base.h"
#include "../core/utility.h"

class CombatSystem : public GameSystemBase {
public:
    void handleAttack(EntityId attacker, EntityId defender);

private:
    void handleAttackEntityEvent(const AttackEntityEvent* event) override;

    void updateLog(const EntityId& attacker, const EntityId& target,
                   int damage);
    void killEntity(EntityId id);
};
