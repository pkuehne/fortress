#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include "entity.h"
#include "component_base.h"
#include <map>
#include <unordered_set>

typedef std::unordered_set<ComponentBase*> ComponentHolder;

class ComponentManager {
public:
    void add (EntityId entity, ComponentBase* component) {
        m_components[entity].insert (component); //Todo: Check that we don't already have this type
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
            if (found) {
                delete component;
                m_components[entity].erase (found);
                break;
            }
        }
    }
    void removeAll (EntityId entity) {
        for (ComponentBase* component : m_components[entity]) {
            delete component;
        }
        m_components[entity].clear();
    }

    ComponentHolder& getAll (EntityId id) {
        return m_components[id];
    }

private:
    std::map<EntityId, ComponentHolder> m_components;
};

#endif
