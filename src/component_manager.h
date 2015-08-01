#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include "component_manager_interface.h"
#include "entity.h"
#include <map>

template <class T>
class ComponentManager : public ComponentManagerInterface<T> {
public:
    void add (EntityId entity, T component);
    T* get (EntityId entity);
    void remove (EntityId entity);
    std::map<EntityId, T>& getAll() { return m_components; }

private:
    std::map<EntityId, T> m_components;
};

template <class T>
void ComponentManager<T>::add (EntityId entity, T component)
{
    m_components[entity] = component;
}

template <class T>
void ComponentManager<T>::remove (EntityId entity)
{
    m_components.erase (entity);
}

template <class T>
T* ComponentManager<T>::get (EntityId entity)
{
    typename std::map<EntityId, T>::iterator it = m_components.find (entity);
    if (it == m_components.end()) {
        return 0;
    }
    return &(it->second);
}

#endif
