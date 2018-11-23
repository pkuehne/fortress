#pragma once

#include "../core/game_system_base.h"

class EquipmentSystem : public GameSystemBase {
public:
    void registerHandlers();

private:
    void handleDropEquipmentEvent(std::shared_ptr<DropEquipmentEvent> event);
    void
    handlePickupEquipmentEvent(std::shared_ptr<PickupEquipmentEvent> event);
    void handleUnequipItemEvent(std::shared_ptr<UnequipItemEvent> event);
    void handleEquipItemEvent(std::shared_ptr<EquipItemEvent> event);
    void handleConsumeItemEvent(std::shared_ptr<ConsumeItemEvent> event);
};
