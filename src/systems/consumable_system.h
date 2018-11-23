#include "../core/game_system_base.h"
#include "../core/utility.h"

class ConsumableSystem : public GameSystemBase {
public:
    void registerHandlers();

private:
    void handleConsumeItemEvent(std::shared_ptr<ConsumeItemEvent> event);
};
