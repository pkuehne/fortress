#pragma once

#include "component_base.h"
#include <string>

struct DescriptionComponent : public ComponentBase {
    std::string title;
    std::string text;
};

