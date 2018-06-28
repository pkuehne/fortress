#ifndef EQUIPMENT_COMPONENT_H
#define EQUIPMENT_COMPONENT_H

#include "../core/entity.h"
#include "component_base.h"
#include <vector>

struct EquipmentComponent : public ComponentBase {
    EntityId headWearable;
    EntityId faceWearable;
    EntityId chestWearable;
    EntityId armsWearable;
    EntityId handsWearable;
    EntityId legsWearable;
    EntityId feetWearable;

    EntityId rightHandWieldable;
    EntityId leftHandWieldable;

    std::vector<EntityId> carriedEquipment;
    int maxCarryWeight;
    int maxCarryVolume;
    EquipmentComponent()
        : headWearable(0), faceWearable(0), chestWearable(0), armsWearable(0),
          handsWearable(0), legsWearable(0), feetWearable(0),
          rightHandWieldable(0), leftHandWieldable(0) {}
};

#endif
