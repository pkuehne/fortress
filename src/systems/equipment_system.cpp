#include "equipment_system.h"
#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/equipment_component.h"
#include "../components/sprite_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"

void unequipItem(EntityId item, EquipmentComponent* equipment) {
    if (item == equipment->rightHandWieldable) {
        equipment->rightHandWieldable = 0;
    } else if (item == equipment->leftHandWieldable) {
        equipment->leftHandWieldable = 0;
    } else if (item == equipment->headWearable) {
        equipment->headWearable = 0;
    } else if (item == equipment->faceWearable) {
        equipment->faceWearable = 0;
    } else if (item == equipment->armsWearable) {
        equipment->armsWearable = 0;
    } else if (item == equipment->chestWearable) {
        equipment->chestWearable = 0;
    } else if (item == equipment->legsWearable) {
        equipment->legsWearable = 0;
    } else if (item == equipment->feetWearable) {
        equipment->feetWearable = 0;
    }
}

bool equipItem(EntityId item, WieldableComponent* wieldable,
               WearableComponent* wearable, EquipmentComponent* equipment) {
    if (wieldable != 0) {
        if (wieldable->position == WieldableRightHand ||
            wieldable->position == WieldableBothHands) {
            equipment->rightHandWieldable = item;
            return true;
        }
        if (wieldable->position == WieldableLeftHand ||
            wieldable->position == WieldableBothHands) {
            equipment->leftHandWieldable = item;
            return true;
        }
    }
    if (wearable != 0) {
        if (wearable->position == WearableHead) {
            equipment->headWearable = item;
            return true;
        }
        if (wearable->position == WearableFace) {
            equipment->faceWearable = item;
            return true;
        }
        if (wearable->position == WearableArms) {
            equipment->armsWearable = item;
            return true;
        }
        if (wearable->position == WearableChest) {
            equipment->chestWearable = item;
            return true;
        }
        if (wearable->position == WearableLegs) {
            equipment->legsWearable = item;
            return true;
        }
        if (wearable->position == WearableFeet) {
            equipment->feetWearable = item;
            return true;
        }
    }
    return false;
}

void EquipmentSystem::registerHandlers() {
    events()->subscribe<DropEquipmentEvent>(
        [=](std::shared_ptr<DropEquipmentEvent> event) {
            handleDropEquipmentEvent(event);
        });
    events()->subscribe<PickupEquipmentEvent>(
        [=](std::shared_ptr<PickupEquipmentEvent> event) {
            handlePickupEquipmentEvent(event);
        });
    events()->subscribe<EquipItemEvent>(
        [=](std::shared_ptr<EquipItemEvent> event) {
            handleEquipItemEvent(event);
        });
    events()->subscribe<UnequipItemEvent>(
        [=](std::shared_ptr<UnequipItemEvent> event) {
            handleUnequipItemEvent(event);
        });
    events()->subscribe<ConsumeItemEvent>(
        [=](std::shared_ptr<ConsumeItemEvent> event) {
            handleConsumeItemEvent(event);
        });
}

void EquipmentSystem::handleDropEquipmentEvent(
    std::shared_ptr<DropEquipmentEvent> event) {
    EquipmentComponent* equipment =
        components()->get<EquipmentComponent>(event->entity);

    unequipItem(event->item, equipment);

    std::vector<EntityId>::iterator it = equipment->carriedEquipment.begin();
    for (; it != equipment->carriedEquipment.end(); ++it) {
        if (*it == event->item) {
            equipment->carriedEquipment.erase(it);
            break;
        }
    }

    Location location = entities()->getLocation(event->entity);
    entities()->setLocation(event->item, location);
}

void EquipmentSystem::handlePickupEquipmentEvent(
    std::shared_ptr<PickupEquipmentEvent> event) {
    EquipmentComponent* equipment =
        components()->get<EquipmentComponent>(event->entity);

    Location invalid;
    entities()->setLocation(event->item, invalid);

    equipment->carriedEquipment.push_back(event->item);
}

void EquipmentSystem::handleEquipItemEvent(
    std::shared_ptr<EquipItemEvent> event) {
    EquipmentComponent* equipment =
        components()->get<EquipmentComponent>(event->entity);
    WearableComponent* wearable =
        components()->get<WearableComponent>(event->item);
    WieldableComponent* wieldable =
        components()->get<WieldableComponent>(event->item);

    if (equipItem(event->item, wieldable, wearable, equipment)) {
        std::vector<EntityId>::iterator it =
            equipment->carriedEquipment.begin();
        for (; it != equipment->carriedEquipment.end(); ++it) {
            if (*it == event->item) {
                equipment->carriedEquipment.erase(it);
                break;
            }
        }
    }
}

void EquipmentSystem::handleUnequipItemEvent(
    std::shared_ptr<UnequipItemEvent> event) {
    EquipmentComponent* equipment =
        components()->get<EquipmentComponent>(event->entity);
    unequipItem(event->item, equipment);
    equipment->carriedEquipment.push_back(event->item);
}

void EquipmentSystem::handleConsumeItemEvent(
    std::shared_ptr<ConsumeItemEvent> event) {
    EquipmentComponent* equipment =
        components()->get<EquipmentComponent>(event->entity);
    std::vector<EntityId>::iterator it = equipment->carriedEquipment.begin();
    for (; it != equipment->carriedEquipment.end(); ++it) {
        if (*it == event->item) {
            equipment->carriedEquipment.erase(it);
            break;
        }
    }
}