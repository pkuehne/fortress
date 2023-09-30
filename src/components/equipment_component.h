#pragma once

#include "../core/entity.h"
#include <vector>

struct EquipmentComponent {
    EntityId headWearable = 0;
    EntityId faceWearable = 0;
    EntityId chestWearable = 0;
    EntityId armsWearable = 0;
    EntityId handsWearable = 0;
    EntityId legsWearable = 0;
    EntityId feetWearable = 0;

    EntityId rightHandWieldable = 0;
    EntityId leftHandWieldable = 0;

    int maxCarryWeight = 0;
    int maxCarryVolume = 0;
    std::vector<EntityId> carriedEquipment;
};
