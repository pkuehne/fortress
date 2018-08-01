#include "game_system_base.h"

void GameSystemBase::handleEvent(std::shared_ptr<Event> i_event) {
    Event* event = i_event.get();
    switch (event->getType()) {
        case EVENT_ADD_ENTITY: {
            handleAddEntityEvent(dynamic_cast<const AddEntityEvent*>(event));
            break;
        }
        case EVENT_REMOVE_ENTITY: {
            handleRemoveEntityEvent(
                dynamic_cast<const RemoveEntityEvent*>(event));
            break;
        }
        case EVENT_OPEN_ENTITY: {
            handleOpenEntityEvent(dynamic_cast<const OpenEntityEvent*>(event));
            break;
        }
        case EVENT_CLOSE_ENTITY: {
            handleCloseEntityEvent(
                dynamic_cast<const CloseEntityEvent*>(event));
            break;
        }
        case EVENT_ATTACK_ENTITY: {
            handleAttackEntityEvent(
                dynamic_cast<const AttackEntityEvent*>(event));
            break;
        }
        case EVENT_CONSUME_ITEM: {
            handleConsumeItemEvent(
                dynamic_cast<const ConsumeItemEvent*>(event));
            break;
        }
        case EVENT_DROP_EQUIPMENT: {
            handleDropEquipmentEvent(
                dynamic_cast<const DropEquipmentEvent*>(event));
            break;
        }
        case EVENT_PICKUP_EQUIPMENT: {
            handlePickupEquipmentEvent(
                dynamic_cast<const PickupEquipmentEvent*>(event));
            break;
        }
        case EVENT_EQUIP_ITEM: {
            handleEquipItemEvent(dynamic_cast<const EquipItemEvent*>(event));
            break;
        }
        case EVENT_UNEQUIP_ITEM: {
            handleUnequipItemEvent(
                dynamic_cast<const UnequipItemEvent*>(event));
            break;
        }
        case EVENT_MOVE_ENTITY: {
            handleMoveEntityEvent(dynamic_cast<const MoveEntityEvent*>(event));
            break;
        }
        case EVENT_START_CONVERSATION: {
            handleStartConversationEvent(
                dynamic_cast<const StartConversationEvent*>(event));
            break;
        }
        default:
            break;
    }
}