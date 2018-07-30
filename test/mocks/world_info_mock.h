#pragma once

#include "../../src/world/world_info.h"
#include <gmock/gmock.h>

class WorldInfoMock : public WorldInfo {
public:
    MOCK_METHOD0(getGroupings, GroupingManager&());
};
