#include "quest.h"
#include "game_state.h"

#include <iostream>

void KillQuest::update(GameState& state)
{
    bool found = false;
    for (auto area : state.map()->getAreas()) {
        for (EntityId entity : state.entityManager()->get(area.first)) {
            if (entity == m_target) {
                found = true;
            }
        }
    }
    isCompleted() = !found;
}
