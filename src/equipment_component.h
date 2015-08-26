#ifndef EQUIPMENT_COMPONENT_H
#define EQUIPMENT_COMPONENT_H

#include "entity.h"
#include <vector>

struct EquipmentComponent {
    EntityId    rightHandWearable;
    EntityId    leftHandWearable;
    EntityId    rightArmWearable;
    EntityId    leftArmWearable;
    EntityId    headWearable;
    EntityId    faceWearable;
    EntityId    torsoWearable;
    EntityId    chestWearable;
    EntityId    lowerBodyWearable;
    EntityId    rightLegWearable;
    EntityId    leftLegWearable;
    EntityId    rightFootWearable;
    EntityId    leftFootWearable;

    EntityId    rightHandWieldable;
    EntityId    leftHandWieldable;

    std::vector<EntityId> carriedEquipment;
    int         maxCarryWeight;
    int         maxCarryVolume;
};

#endif
