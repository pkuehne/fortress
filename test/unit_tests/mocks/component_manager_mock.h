#pragma once

#include "../../src/core/component_manager.h"
#include <gmock/gmock.h>

class DescriptionComponent;

class ComponentManagerMock : public ComponentManager {
public:
    MOCK_METHOD1(removeAll, void(EntityId));
    MOCK_METHOD2(add, void(EntityId, ComponentBase*));
};