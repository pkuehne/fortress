#ifndef COMPONENT_MANAGER_MOCK_H
#define COMPOENNT_MANAGER_MOCK_H

#include <component_manager_interface.h>
#include <gmock/gmock.h>

template<class T>
class ComponentManagerMock : public ComponentManagerInterface<T> {
public:
    MOCK_METHOD2_T (add, void (EntityId entity, T component));
    MOCK_METHOD1_T (get, T* (EntityId entity));
    MOCK_METHOD1_T (remove, void (EntityId entity));
    MOCK_METHOD0_T (getAll, std::map<EntityId, T>&());
};

#endif
