#include "map_generator_system.h"
#include "../components/connector_component.h"
#include "../generators/dungeon_generator.h"
#include "../generators/rural_generator.h"
#include <spdlog/spdlog.h>

void MapGeneratorSystem::registerHandlers() {
    auto generateHandler = [this](auto event) { this->generate(event); };
    events()->subscribe<GenerateRuralMapEvent>(generateHandler);
}

void MapGeneratorSystem::generate(const GenerateRuralMapEvent& event) {
    unsigned int startArea = map()->createArea(event.width, event.height, 1);

    RuralGenerator rural;
    rural.initialise(events(), entities(), map());
    rural.mapHeight() = event.height;
    rural.mapWidth() = event.width;
    rural.area() = startArea;
    rural.generate();

    for (EntityId stair : rural.getAreaLinks()) {
        int retries = 0;
        bool success = false;
        unsigned int area =
            map()->createArea(event.width, event.height, event.depth);

        spdlog::info("Generating area: {}", area);
        DungeonGenerator l_generator;
        l_generator.initialise(events(), entities(), map());
        l_generator.maxDepth() = event.depth;
        l_generator.mapHeight() = event.height;
        l_generator.mapWidth() = event.width;
        l_generator.area() = area;
        l_generator.numberOfRooms() = event.rooms;
        l_generator.downStairTarget() = 0;
        l_generator.upStairTarget() = stair;
        if (area == 2) {
            l_generator.createBoss() = true;
        }
        do {
            success = l_generator.generate();
        } while (!success && retries++ < 20);
        if (!success) {
            spdlog::error("Failed to generate a valid map");
        }
        entities()->world().entity(stair).set<ConnectorComponent>(
            {l_generator.upStairLink()});
    }
    spdlog::info("Placed {} entities!", entities()->getMaxId());
    events()->fire<MapGeneratedEvent>();
}