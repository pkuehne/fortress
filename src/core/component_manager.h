#pragma once

#include "../components/component_base.h"
#include "../core/entity.h"
#include <glog/logging.h>
#include <map>
#include <memory>
#include <typeinfo>

using ComponentHolder = std::map<size_t, std::unique_ptr<ComponentBase>>;

/// @brief Manages the lifetime of components
class ComponentManager {
public:
    ComponentManager() = default;
    virtual ~ComponentManager() = default;

    /// @brief Create in-place a new Component attached to this entity
    /// @param[in] entity The entity to create the component for
    /// @returns The created component
    template <class T> T* make(EntityId entity) {
        ComponentHolder& holder = m_components[entity];
        size_t hash_code = typeid(T).hash_code();
        if (holder.find(hash_code) == holder.end()) {
            holder[hash_code] = std::make_unique<T>();
        } else {
            LOG(WARNING) << "Tried to add existing component "
                         << typeid(T).name() << " to Entity " << entity
                         << std::endl;
        }

        return dynamic_cast<T*>(holder[hash_code].get());
    }

    /// @brief Return a component attached to this entity
    /// @param[in] entity The entity to return the component for
    /// @returns The component if it exists, otherwise nullptr
    template <class T> T* get(EntityId entity) {
        auto& components = m_components[entity];
        if (components.find(typeid(T).hash_code()) == components.end()) {
            return nullptr;
        }
        return dynamic_cast<T*>(
            m_components[entity][typeid(T).hash_code()].get());
    }

    /// @brief Return whether the given Component exists for this entity
    /// @param[in] entity The entity to check the component for
    /// @returns true if there is such a component, false otherwise
    template <class T> bool exists(EntityId entity) {
        auto& components = m_components[entity];
        return components.find(typeid(T).hash_code()) != components.end();
    }

    /// @brief Remove a given component attached
    /// @param[in] entity The entity to remove the component from
    template <class T> void remove(EntityId entity) {
        auto& components = m_components[entity];
        auto it = components.find(typeid(T).hash_code());
        if (it != components.end()) {
            components.erase(it);
        }
    }

    /// @brief Removes all components from an entity
    /// @param[in] entity The entity to remove the components from
    void removeAll(EntityId entity) { m_components[entity].clear(); }

    /// @brief Returns all components attached to an entity
    /// @param[in] entity The entity to return all components for
    /// @returns A list of components
    const ComponentHolder& getAll(EntityId id) { return m_components[id]; }

private:
    std::map<EntityId, ComponentHolder> m_components;
};
