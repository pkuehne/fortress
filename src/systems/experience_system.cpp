#include "experience_system.h"
#include "../components/experience_component.h"
#include <cmath>

void ExperienceSystem::registerHandlers() {
    events()->subscribe(HandlerFunc<UpdateExperienceEvent>(
        [=](std::shared_ptr<UpdateExperienceEvent> event) {
            auto experienceComp =
                components()->get<ExperienceComponent>(event->entity);
            if (!experienceComp) {
                return;
            }
            experienceComp->xp += event->experience;
            events()->raise(std::make_shared<AddLogMessageEvent>(
                "You have gained experience!"));

            unsigned int newLevel =
                0.025f * sqrt(static_cast<double>(experienceComp->xp));

            if (newLevel > experienceComp->level) {
                experienceComp->level = newLevel;
                events()->raise(std::make_shared<AddLogMessageEvent>(
                    "You have levelled up!"));
                events()->raise(
                    std::make_shared<LevelUpEvent>(event->entity, newLevel));
            }
        }));
}