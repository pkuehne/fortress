#include "experience_system.h"
#include "../components/experience_component.h"
#include <cmath>

void ExperienceSystem::registerHandlers() {
    events()->subscribe<UpdateExperienceEvent>(
        [=](std::shared_ptr<UpdateExperienceEvent> event) {
            auto experienceComp =
                components()->get<ExperienceComponent>(event->entity);
            if (!experienceComp) {
                return;
            }
            experienceComp->xp += event->experience;
            experienceComp->level =
                0.025f * sqrt(static_cast<double>(experienceComp->xp));
            std::cout << experienceComp->level << ": " << experienceComp->xp
                      << std::endl;
        });
}