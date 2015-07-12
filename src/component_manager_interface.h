#ifndef COMPONENT_MANAGER_INTERFACE_H
#define COMPONENT_MANAGER_INTERFACE_H

#include "entity.h"
#include <map>

template <class T>
class ComponentManagerInterface {
public:
    virtual ~ComponentManagerInterface() { }
    virtual void add (Entity* entity, T component) = 0;
    virtual T* get (Entity* entity) = 0;
    virtual void remove (Entity* entity) = 0;
    virtual std::map<Entity*, T>& getAll() = 0;
};

#endif
