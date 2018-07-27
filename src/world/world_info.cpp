#include "world_info.h"
#include "grouping_manager.h"

WorldInfo::WorldInfo() : m_groupings(std::make_unique<GroupingManager>()) {
    //
}

WorldInfo::~WorldInfo() {
    //
}