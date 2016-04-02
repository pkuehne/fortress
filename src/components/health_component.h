#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component_base.h"

struct HealthComponent : public ComponentBase {
    unsigned int health = 10;
    unsigned int thirst = 0;
    unsigned int hunger = 0;

    unsigned int thirstRate = 30;
    unsigned int hungerRate = 40;

    unsigned int thirstStep = 0;
    unsigned int hungerStep = 0;
};

#endif
