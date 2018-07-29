#pragma once

#include "../../src/core/component_manager.h"
#include <gmock/gmock.h>

class DescriptionComponent;

class ComponentManagerMock : public ComponentManager {
public:
    MOCK_METHOD1(removeAll, void(EntityId));
    MOCK_METHOD1(make_description, DescriptionComponent*(EntityId));

    template <class T> T* make(EntityId entity) {}
};

// template <> DescriptionComponent* ComponentManagerMock::make(EntityId entity)
// {
//     return make_description(entity);
// }
