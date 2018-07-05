#ifndef DESCRIPTION_COMPONENT_H
#define DESCRIPTION_COMPONENT_H

#include "component_base.h"
#include <string>

struct DescriptionComponent : public ComponentBase {
    std::string title;
    std::string text;
};

#endif
