#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component_base.h"

struct HealthComponent : public ComponentBase {
    unsigned int health;
    unsigned int thirst;
    unsigned int hunger;
};

#endif
