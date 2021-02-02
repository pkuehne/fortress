#pragma once

#include "../core/game_system_base.h"

class EquipmentSystem : public GameSystemBase {
public:
    void registerHandlers() override;

private:
    void handleDropEquipmentEvent(const DropEquipmentEvent& event);
    void handlePickupEquipmentEvent(const PickupEquipmentEvent& event);
    void handleUnequipItemEvent(const UnequipItemEvent& event);
    void handleEquipItemEvent(const EquipItemEvent& event);
    void handleConsumeItemEvent(const ConsumeItemEvent& event);
    void handleKillEntityEvent(const KillEntityEvent& event);
};
