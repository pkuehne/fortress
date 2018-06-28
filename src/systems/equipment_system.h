#ifndef EQUIPMENT_SYSTEM
#define EQUIPMENT_SYSTEM

#include "../core/game_system_base.h"

class EquipmentSystem : public GameSystemBase {
public:
    void handleEvent(const Event* event);
};

#endif
