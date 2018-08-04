#include "component_manager.h"
#include <glog/logging.h>

void ComponentManager::add(EntityId entity, ComponentBase* component) {
    // if (component == nullptr) {
    //     LOG(WARNING) << "Can't add a nullptr" << std::endl;
    //     throw std::string("Tried to add nullptr component");
    // }

    ComponentHolder& holder = m_components[entity];
    auto iter = holder.find(typeid(*component).name());
    if (iter == holder.end()) {
        holder[typeid(*component).name()] = component;
    } else {
        LOG(WARNING) << "Tried to add existing component "
                     << typeid(*component).name() << " to Entity " << entity
                     << std::endl;
        return;
    }
}
