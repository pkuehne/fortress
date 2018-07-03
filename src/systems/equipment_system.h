#pragma once

#include "../core/game_system_base.h"

class EquipmentSystem : public GameSystemBase {
private:
    void handleDropEquipmentEvent(const DropEquipmentEvent* event) override;
    void handlePickupEquipmentEvent(const PickupEquipmentEvent* event) override;
    void handleUnequipItemEvent(const UnequipItemEvent* event) override;
    void handleEquipItemEvent(const EquipItemEvent* event) override;
    void handleConsumeItemEvent(const ConsumeItemEvent* event) override;
};
