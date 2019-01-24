#include "core/game_engine.h"
#include "core/graphics.h"
#include "systems/combat_system.h"
#include "systems/consumable_system.h"
#include "systems/dialog_system.h"
#include "systems/equipment_system.h"
#include "systems/graphics_effect_system.h"
#include "systems/health_system.h"
#include "systems/interaction_system.h"
#include "systems/movement_system.h"
#include "systems/npc_system.h"
#include "systems/objectives_system.h"
#include "systems/prefab_system.h"
#include <cstdlib>
#include <execinfo.h>
#include <glog/logging.h>
#include <iostream>
#include <signal.h>

void handler(int signal) {
    const unsigned int numFrames = 100;
    void* frames[numFrames] = {0};
    size_t stackSize = backtrace(frames, numFrames);
    char** symbols = 0;

    std::cerr << "!!!CRASH!!! Caught Segmentation Violation: " << signal
              << std::endl;
    symbols = backtrace_symbols(frames, stackSize);
    if (symbols == 0) {
        std::cerr << "Failed to load back trace symbols!" << std::endl;
        exit(1);
    }

    for (unsigned int ii = 0; ii < stackSize; ii++) {
        std::cerr << ii << ". " << symbols[ii] << std::endl;
    }

    exit(1);
}

int main(int argc, char** argv) {
    // Install Segmentation Fault handler
    signal(SIGSEGV, handler);
    FLAGS_log_dir = "artifacts/logs/";
    google::InitGoogleLogging(argv[0]);

    try {
        Graphics* l_graphics = new Graphics();
        l_graphics->initialise(argc, argv);
        GameEngine* l_engine = new GameEngine(l_graphics);

        l_engine->addSystem(new MovementSystem());
        l_engine->addSystem(new CombatSystem());
        l_engine->addSystem(new NpcSystem());
        l_engine->addSystem(new ObjectivesSystem());
        l_engine->addSystem(new EquipmentSystem());
        l_engine->addSystem(new ConsumableSystem());
        l_engine->addSystem(new GraphicsEffectSystem());
        l_engine->addSystem(new HealthSystem());
        l_engine->addSystem(new InteractionSystem());
        l_engine->addSystem(new DialogSystem());
        l_engine->addSystem(new PrefabSystem());
        l_engine->initialise();
        l_graphics->spin();
    } catch (char const* err) {
        std::cerr << "Main: Exception caught: " << err << std::endl;
    } catch (const std::string& err) {
        std::cerr << "Main: Exception caught: " << err << std::endl;
    }
    return 0;
}
