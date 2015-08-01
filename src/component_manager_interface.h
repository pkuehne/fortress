#ifndef COMPONENT_MANAGER_INTERFACE_H
#define COMPONENT_MANAGER_INTERFACE_H

#include "entity.h"
#include <map>

template <class T>
class ComponentManagerInterface {
public:
    virtual ~ComponentManagerInterface() { }
    virtual void add (EntityId entity, T component) = 0;
    virtual T* get (EntityId entity) = 0;
    virtual void remove (EntityId entity) = 0;
    virtual std::map<EntityId, T>& getAll() = 0;
};

#endif
