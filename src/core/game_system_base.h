#ifndef GAME_SYSTEM_BASE_H
#define GAME_SYSTEM_BASE_H

#include "event.h"
#include "game_engine.h"
#include "game_system_interface.h"
#include <vector>

class GameSystemBase : public GameSystemInterface {
public:
    GameSystemBase() : m_engine(0) {}
    virtual ~GameSystemBase() {}

    virtual void initialise(GameEngine* engine) { m_engine = engine; }
    virtual GameEngine* getEngine() { return m_engine; }
    virtual void handleEvent(const Event* event);
    virtual void update() {}

    virtual void handleAddEntityEvent(const AddEntityEvent* event) {}
    virtual void handleRemoveEntityEvent(const RemoveEntityEvent* event) {}
    virtual void handleOpenEntityEvent(const OpenEntityEvent* event) {}
    virtual void handleCloseEntityEvent(const CloseEntityEvent* event) {}
    virtual void handleAttackEntityEvent(const AttackEntityEvent* event) {}
    virtual void handleConsumeItemEvent(const ConsumeItemEvent* event) {}
    virtual void handleDropEquipmentEvent(const DropEquipmentEvent* event) {}
    virtual void handlePickupEquipmentEvent(const PickupEquipmentEvent* event) {
    }
    virtual void handleEquipItemEvent(const EquipItemEvent* event) {}
    virtual void handleUnequipItemEvent(const UnequipItemEvent* event) {}
    virtual void handleMoveEntityEvent(const MoveEntityEvent* event) {}

protected:
    GameEngine* m_engine;
};

#endif
