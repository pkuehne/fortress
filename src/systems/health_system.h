#include "../core/game_system_base.h"

class HealthSystem : public GameSystemBase {
public:
    virtual void handleEvent(const Event* event) override;
    virtual void update() override;
};
