#ifndef DESCRIPTION_COMPONENT_H
#define DESCRIPTION_COMPONENT_H

#include "base_component.h"
struct DescriptionComponent : public BaseComponent {
    std::string title;
    std::string text;
};

#endif
