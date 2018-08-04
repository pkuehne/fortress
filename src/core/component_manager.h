#pragma once

#include "../components/component_base.h"
#include "../core/entity.h"
#include <map>
#include <typeinfo>

typedef std::map<std::string, ComponentBase*> ComponentHolder;

/// @brief Manages the lifetime of components
class ComponentManager {
public:
    ComponentManager() = default;
    virtual ~ComponentManager() = default;

    /// @brief Create in-place a new Component attached to this entity
    /// @param[in] entity The entity to create the component for
    /// @returns The created component
    template <class T> T* make(EntityId entity) {
        T* component = new T();
        this->add(entity, component);
        return component;
    }

    /// @brief Return a component attached to this entity
    /// @param[in] entity The entity to return the component for
    /// @returns The component if it exists, otherwise nullptr
    template <class T> T* get(EntityId entity) {
        for (auto& iter : m_components[entity]) {
            T* retval = dynamic_cast<T*>(iter.second);
            if (retval) {
                return retval;
            }
        }
        return nullptr;
    }

    /// @brief Remove a given component attached
    /// @param[in] entity The entity to remove the component from
    template <class T> void remove(EntityId entity) {
        for (auto& iter : m_components[entity]) {
            T* found = dynamic_cast<T*>(iter.second);
            if (found) {
                m_components[entity].erase(iter.first);
                delete found;
                break;
            }
        }
    }

    /// @brief Removes all components from an entity
    /// @param[in] entity The entity to remove the components from
    void removeAll(EntityId entity) {
        for (auto& iter : m_components[entity]) {
            delete iter.second;
        }
        m_components[entity].clear();
    }

    /// @brief Returns all components attached to an entity
    /// @param[in] entity The entity to return all components for
    /// @returns A list of components
    ComponentHolder& getAll(EntityId id) { return m_components[id]; }

private:
    virtual void add(EntityId entity, ComponentBase* component);

private:
    std::map<EntityId, ComponentHolder> m_components;
};
