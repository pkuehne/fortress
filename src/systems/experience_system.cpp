#include "experience_system.h"
#include "../components/experience_component.h"
#include <cmath>

void ExperienceSystem::registerHandlers() {
    events()->subscribe<UpdateExperienceEvent>([=](auto event) {
        auto experienceComp =
            components()->get<ExperienceComponent>(event.entity);
        if (!experienceComp) {
            return;
        }
        experienceComp->xp += event.experience;
        events()->fire<AddLogMessageEvent>("You have gained experience!");

        unsigned int newLevel =
            0.025f * sqrt(static_cast<double>(experienceComp->xp));

        if (newLevel > experienceComp->level) {
            experienceComp->level = newLevel;
            events()->fire<AddLogMessageEvent>("You have levelled up!");
            events()->fire<LevelUpEvent>(event.entity, newLevel);
        }
    });
}