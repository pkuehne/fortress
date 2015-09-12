#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include "entity.h"
#include "component_base.h"
#include <map>

class ComponentManager {
public:
    void add (EntityId entity, ComponentBase* component) {
        m_components[entity].insert (component);
    }

    template <class T>
    T* get (EntityId entity) {
      for (ComponentBase* component : m_components[entity]) {
            T* retval = dynamic_cast<T*> (component);
            if (retval) return retval;
        }
        return nullptr;
    }

    template <class T>
    void remove (EntityId entity) {
        for (ComponentBase* component : m_components[entity]) {
            T* found = dynamic_cast<T*> (component);
            if (found) m_components[entity].erase (found);
        }
    }
    void removeAll (EntityId entity) {
        m_components.clear();
    }

private:
    std::map<EntityId, std::unordered_set<ComponentBase*>> m_components;
};

#endif
