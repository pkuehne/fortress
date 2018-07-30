#pragma once

#include "../../src/world/grouping_manager.h"
#include <gmock/gmock.h>

class GroupingManagerMock : public GroupingManager {
public:
    MOCK_METHOD2(addEntityToGrouping,
                 void(EntityId entity, const std::string& name));
};
