#pragma once

#include "../../src/core/entity_manager.h"
#include <gmock/gmock.h>

class EntityManagerMock : public EntityManager {
public:
    MOCK_METHOD1(createEntity, EntityId(const Location&));
};
