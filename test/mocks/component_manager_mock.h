#pragma once

#include "../../src/core/component_manager.h"
#include <gmock/gmock.h>

class ComponentManagerMock : public ComponentManager {
public:
    MOCK_METHOD1(removeAll, void(EntityId));
};
