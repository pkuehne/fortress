#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include "entity.h"
#include <map>

template <class T>
class ComponentManager {
public:
    void add (Entity* entity, T component);
    T* get (Entity* entity);
    void remove (Entity* entity);
    std::map<Entity*, T>& getAll() { return m_components; }
private:
    std::map<Entity*, T> m_components;
};

template <class T>
void ComponentManager<T>::add (Entity* entity, T component)
{
    m_components[entity] = component;
}

template <class T>
void ComponentManager<T>::remove (Entity* entity)
{
    m_components.erase (entity);
}

template <class T>
T* ComponentManager<T>::get (Entity* entity)
{
    typename std::map<Entity*, T>::iterator it = m_components.find (entity);
    if (it == m_components.end()) {
        return 0;
    }
    return &(it->second);
}

#endif
