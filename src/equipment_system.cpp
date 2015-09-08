#include "equipment_system.h"

void EquipmentSystem::handleEvent (const Event* event) {
    switch (event->getType()) {
        case EVENT_DROP_EQUIPMENT: {
            const DropEquipmentEvent* l_event = dynamic_cast<const DropEquipmentEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(l_event->entity);
            LocationComponent* location = getEngine()->getEntities()->getLocations()->get(l_event->entity);
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
            SpriteComponent sprite;
            sprite.fgColor = Color (RED);
            sprite.sprite = '*';
            getEngine()->getEntities()->getSprites()->add (l_event->item, sprite);

            LocationComponent loc;
            loc.x = location->x;
            loc.y = location->y;
            loc.z = location->z;
            getEngine()->getEntities()->getLocations()->add (l_event->item, loc);

            break;
        }
        case EVENT_PICKUP_EQUIPMENT: {
            const PickupEquipmentEvent* l_event = dynamic_cast<const PickupEquipmentEvent*> (event);
            EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(l_event->entity);
            getEngine()->getEntities()->getSprites()->remove(l_event->item);
            getEngine()->getEntities()->getLocations()->remove(l_event->item);

            equipment->carriedEquipment.push_back (l_event->item);

            break;
        }
        default: break;
    }
}
