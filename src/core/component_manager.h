#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include "entity.h"
#include "component_base.h"
#include <map>
#include <unordered_set>
#include <typeinfo>
#include <iostream>

//typedef std::unordered_set<ComponentBase*> ComponentHolder;
typedef std::map<std::string, ComponentBase*> ComponentHolder;

class ComponentManager {
public:
    void add (EntityId entity, ComponentBase* component) {
        //m_components[entity].insert (component); //Todo: Check that we don't already have this type
        ComponentHolder& holder = m_components[entity];
        auto iter = holder.find (typeid(*component).name());
        if (iter == holder.end()) {
            holder[typeid(*component).name()] = component;
        } else {
            std::cout << "Tried to add existing component" << std::endl;
        }

    }

    template <class T>
    T* get (EntityId entity) {
      for (auto& iter : m_components[entity]) {
            T* retval = dynamic_cast<T*> (iter.second);
            if (retval) return retval;
        }
        return nullptr;
    }

    template <class T>
    void remove (EntityId entity) {
        for (auto& iter : m_components[entity]) {
            T* found = dynamic_cast<T*> (iter.second);
            if (found) {
                //m_components[entity].erase (iter);
                delete found;
                break;
            }
        }
    }
    void removeAll (EntityId entity) {
        for (auto& iter : m_components[entity]) {
            delete iter.second;
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
