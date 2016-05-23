#include "game_engine.h"
#include "graphics.h"
#include "combat_system.h"
#include "movement_system.h"
#include "objectives_system.h"
#include "equipment_system.h"
#include "npc_system.h"
#include "consumable_system.h"
#include "graphics_effect_system.h"
#include "health_system.h"
#include <cstdlib>
#include <iostream>
#include <execinfo.h>
#include <signal.h>
#include <glog/logging.h>

void handler (int signal) {
    const unsigned int  numFrames   = 100;
    void* frames[numFrames]         = {0};
    size_t stackSize                = backtrace (frames, numFrames);
    char** symbols                  = 0;

    std::cerr << "!!!CRASH!!! Caught Segmentation Violation: " << signal << std::endl;
    symbols = backtrace_symbols (frames, stackSize);
    if (symbols == 0) {
        std::cerr << "Failed to load back trace symbols!" << std::endl;
        exit (1);
    }

    for (unsigned int ii = 0; ii < stackSize; ii++) {
        std::cerr << ii << ". " << symbols[ii] << std::endl;
    }

    exit(1);
}


int main (int argc, char** argv)
{
    // Install Segmentation Fault handler
    signal(SIGSEGV, handler);
    FLAGS_log_dir="artifacts/logs/";
    google::InitGoogleLogging(argv[0]);

    try {
        std::string l_map("testmap.txt");
        if (argc > 1) {
            l_map = argv[1];
        }

        Graphics*   l_graphics = new Graphics();
        l_graphics->initialise(argc, argv);
        GameEngine* l_engine = new GameEngine (l_graphics);

        l_engine->addSystem (new MovementSystem());
        l_engine->addSystem (new CombatSystem());
        l_engine->addSystem (new NpcSystem());
        l_engine->addSystem (new ObjectivesSystem());
        l_engine->addSystem (new EquipmentSystem());
        l_engine->addSystem (new ConsumableSystem());
        l_engine->addSystem (new GraphicsEffectSystem());
        l_engine->addSystem (new HealthSystem());
        l_engine->initialise();
        l_graphics->spin();
    } catch (char const * err) {
        std::cout << err << std::endl;
    }
    return 0;
}
