#include "core/game_engine.h"
#include "core/graphics.h"
#include "systems/combat_system.h"
#include "systems/consumable_system.h"
#include "systems/dialog_system.h"
#include "systems/equipment_system.h"
#include "systems/experience_system.h"
#include "systems/fov_system.h"
#include "systems/graphics_effect_system.h"
#include "systems/health_system.h"
#include "systems/interaction_system.h"
#include "systems/logmessage_system.h"
#include "systems/map_generator_system.h"
#include "systems/movement_system.h"
#include "systems/npc_system.h"
#include "systems/objectives_system.h"
#include "systems/prefab_system.h"
#include <cstdlib>
#include <execinfo.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

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

    auto logger = spdlog::basic_logger_mt("fortress", "./fortress.log", true);
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::info);
    spdlog::set_default_logger(logger);

    try {
        std::shared_ptr<GraphicsInterface> l_graphics =
            std::make_shared<Graphics>();
        l_graphics->initialise(argc, argv);
        GameEngine* l_engine = new GameEngine(l_graphics);

        l_engine->addSystem(new MovementSystem());
        l_engine->addSystem(new CombatSystem());
        l_engine->addSystem(new NpcSystem());
        l_engine->addSystem(new FovSystem());
        // l_engine->addSystem(new ObjectivesSystem());
        l_engine->addSystem(new EquipmentSystem());
        l_engine->addSystem(new ConsumableSystem());
        l_engine->addSystem(new GraphicsEffectSystem());
        l_engine->addSystem(new HealthSystem());
        l_engine->addSystem(new InteractionSystem());
        l_engine->addSystem(new DialogSystem());
        l_engine->addSystem(new PrefabSystem());
        l_engine->addSystem(new ExperienceSystem());
        l_engine->addSystem(new LogMessageSystem());
        l_engine->addSystem(new MapGeneratorSystem());
        l_engine->initialise();
        l_graphics->spin();
    } catch (char const* err) {
        std::cerr << "Main: Exception caught: " << err << std::endl;
    } catch (const std::string& err) {
        std::cerr << "Main: Exception caught: " << err << std::endl;
    }
    return 0;
}
