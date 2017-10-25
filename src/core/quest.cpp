#include "quest.h"
#include "game_state.h"

#include <iostream>

void KillQuest::update(GameState& state)
{
    std::cout << "Checking killed " << m_target  << std::endl;
    bool found = false;
    for (EntityId entity : state.entities()) {
        if (entity == m_target) {
            std::cout << "Found " << m_target << std::endl;
            found = true;
        }
    }
    isCompleted() = !found;
}
