#pragma once

#include "../core/entity.h"
#include "../core/location.h"
#include "../core/utility.h"
#include <map>
#include <vector>

struct NpcComponent {
    std::string stateMachine = "";
    std::string state = "";
    EntityId target = 0;
    unsigned int losDistance = 15;
    std::map<std::string, std::string> attribs;
    std::vector<Location> path;
};
