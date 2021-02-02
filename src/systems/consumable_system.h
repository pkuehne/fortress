#include "../core/game_system_base.h"
#include "../core/utility.h"

class ConsumableSystem : public GameSystemBase {
public:
    void registerHandlers() override;

private:
    void handleConsumeItemEvent(const ConsumeItemEvent& event);
};
