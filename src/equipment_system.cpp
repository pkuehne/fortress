#include "equipment_system.h"
#include "equipment_component.h"
#include "description_component.h"
#include "wearable_component.h"
#include "wieldable_component.h"
#include "sprite_component.h"
#include "droppable_component.h"

void EquipmentSystem::handleEvent (const Event* event) {
    switch (event->getType()) {
        case EVENT_DROP_EQUIPMENT: {
            const DropEquipmentEvent* l_event = dynamic_cast<const DropEquipmentEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getComponents()->get<EquipmentComponent>(l_event->entity);
            if (l_event->item == equipment->rightHandWieldable) {
                equipment->rightHandWieldable = 0;
            }
            if (l_event->item == equipment->leftHandWieldable) {
                equipment->leftHandWieldable = 0;
            }
            if (l_event->item == equipment->headWearable) {
                equipment->headWearable = 0;
            }
            if (l_event->item == equipment->faceWearable) {
                equipment->faceWearable = 0;
            }
            if (l_event->item == equipment->armsWearable) {
                equipment->armsWearable = 0;
            }
            if (l_event->item == equipment->chestWearable) {
                equipment->chestWearable = 0;
            }
            if (l_event->item == equipment->legsWearable) {
                equipment->legsWearable = 0;
            }
            if (l_event->item == equipment->feetWearable) {
                equipment->feetWearable = 0;
            }
            std::vector<EntityId>::iterator it = equipment->carriedEquipment.begin();
            for (;it != equipment->carriedEquipment.end(); it++) {
                if (*it == l_event->item) {
                    equipment->carriedEquipment.erase (it);
                    break;
                }
            }
            SpriteComponent* sprite = new SpriteComponent();
            sprite->fgColor = Color (RED);
            sprite->sprite = '*';
            getEngine()->getComponents()->add (l_event->item, sprite);

            Location location = getEngine()->getEntities()->getLocation(l_event->entity);
            getEngine()->getEntities()->setLocation(l_event->item, location);
            getEngine()->addMessage (INFO, "You drop the item on the ground!");
            break;
        }
        case EVENT_PICKUP_EQUIPMENT: {
            std::cout << "Picking up" << std::endl;
            const PickupEquipmentEvent* l_event = dynamic_cast<const PickupEquipmentEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getComponents()->get<EquipmentComponent>(l_event->entity);
            getEngine()->getComponents()->remove<SpriteComponent>(l_event->item);

            equipment->carriedEquipment.push_back (l_event->item);
            getEngine()->addMessage (INFO, "You pick something up off the ground");
            break;
        }
        case EVENT_UNEQUIP_ITEM: {
            const UnequipItemEvent* l_event = dynamic_cast<const UnequipItemEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getComponents()->get<EquipmentComponent>(l_event->entity);
            if (l_event->item == equipment->rightHandWieldable) {
                equipment->rightHandWieldable = 0;
            }
            if (l_event->item == equipment->leftHandWieldable) {
                equipment->leftHandWieldable = 0;
            }
            if (l_event->item == equipment->headWearable) {
                equipment->headWearable = 0;
            }
            if (l_event->item == equipment->faceWearable) {
                equipment->faceWearable = 0;
            }
            if (l_event->item == equipment->armsWearable) {
                equipment->armsWearable = 0;
            }
            if (l_event->item == equipment->chestWearable) {
                equipment->chestWearable = 0;
            }
            if (l_event->item == equipment->legsWearable) {
                equipment->legsWearable = 0;
            }
            if (l_event->item == equipment->feetWearable) {
                equipment->feetWearable = 0;
            }
            equipment->carriedEquipment.push_back (l_event->item);
            break;
        }
        case EVENT_EQUIP_ITEM: {
            const EquipItemEvent* l_event = dynamic_cast<const EquipItemEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getComponents()->get<EquipmentComponent>(l_event->entity);
            WearableComponent* wearable = getEngine()->getComponents()->get<WearableComponent>(l_event->item);
            WieldableComponent* wieldable = getEngine()->getComponents()->get<WieldableComponent>(l_event->item);
            bool equipped = false;
            if (wieldable != 0) {
                if (wieldable->position == WieldableRightHand || wieldable->position == WieldableBothHands) {
                    equipment->rightHandWieldable = l_event->item; equipped = true;
                }
                if (wieldable->position == WieldableLeftHand || wieldable->position == WieldableBothHands) {
                    equipment->leftHandWieldable = l_event->item; equipped = true;
                }
            }
            if (wearable != 0) {
                if (wearable->position == WearableHead) {
                    equipment->headWearable = l_event->item; equipped = true;
                }
                if (wearable->position == WearableFace) {
                    equipment->faceWearable = l_event->item; equipped = true;
                }
                if (wearable->position == WearableArms) {
                    equipment->armsWearable = l_event->item; equipped = true;
                }
                if (wearable->position == WearableChest) {
                    equipment->chestWearable = l_event->item; equipped = true;
                }
                if (wearable->position == WearableLegs) {
                    equipment->legsWearable = l_event->item; equipped = true;
                }
                if (wearable->position == WearableFeet) {
                    equipment->feetWearable = l_event->item; equipped = true;
                }
            }
            if (equipped) {
                std::vector<EntityId>::iterator it = equipment->carriedEquipment.begin();
                for (;it != equipment->carriedEquipment.end(); it++) {
                    if (*it == l_event->item) {
                        equipment->carriedEquipment.erase(it);
                        break;
                    }
                }
            }
            break;
        }
        default: break;
    }
}