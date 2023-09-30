#include "experience_system.h"
#include "../components/experience_component.h"
#include <cmath>

void ExperienceSystem::registerHandlers() {
    events()->subscribe<UpdateExperienceEvent>(
        [=](auto event) { handleUpdateEvent(event); });
}

void ExperienceSystem::handleUpdateEvent(const UpdateExperienceEvent& event) {
    auto entity = entities()->world().entity(event.entity);
    auto experienceComp = entity.get_mut<ExperienceComponent>();
    if (!experienceComp) {
        return;
    }
    experienceComp->xp += event.experience;
    if (event.entity == entities()->world().lookup("player").id()) {

        events()->fire<AddLogMessageEvent>("You have gained experience!");
    }

    unsigned int newLevel =
        0.025f * sqrt(static_cast<double>(experienceComp->xp));

    if (newLevel > experienceComp->level) {
        experienceComp->level = newLevel;
        if (event.entity == entities()->world().lookup("player").id()) {
            events()->fire<AddLogMessageEvent>("You have levelled up!");
        }
        events()->fire<LevelUpEvent>(event.entity, newLevel);
    }
}