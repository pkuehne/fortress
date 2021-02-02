#include "map_generator_system.h"
#include "../components/connector_component.h"
#include "../generators/dungeon_generator.h"
#include "../generators/rural_generator.h"
#include <glog/logging.h>

void MapGeneratorSystem::registerHandlers() {
    auto generateHandler = [this](auto event) { this->generate(event); };
    events()->subscribe<GenerateRuralMapEvent>(generateHandler);
}

void MapGeneratorSystem::generate(
    std::shared_ptr<GenerateRuralMapEvent> event) {
    unsigned int startArea = map()->createArea(event->width, event->height, 1);

    RuralGenerator rural;
    rural.initialise(events(), components(), entities(), map());
    rural.mapHeight() = event->height;
    rural.mapWidth() = event->width;
    rural.area() = startArea;
    rural.generate();

    for (EntityId stair : rural.getAreaLinks()) {
        int retries = 0;
        bool success = false;
        unsigned int area =
            map()->createArea(event->width, event->height, event->depth);

        LOG(INFO) << "Generating area: " << area << std::endl;
        DungeonGenerator l_generator;
        l_generator.initialise(events(), components(), entities(), map());
        l_generator.maxDepth() = event->depth;
        l_generator.mapHeight() = event->height;
        l_generator.mapWidth() = event->width;
        l_generator.area() = area;
        l_generator.numberOfRooms() = event->rooms;
        l_generator.downStairTarget() = 0;
        l_generator.upStairTarget() = stair;
        if (area == 2) {
            l_generator.createBoss() = true;
        }
        do {
            success = l_generator.generate();
        } while (!success && retries++ < 20);
        if (!success) {
            LOG(ERROR) << "Failed to generate a valid map" << std::endl;
        }
        components()->make<ConnectorComponent>(stair)->target =
            l_generator.upStairLink();
    }
    LOG(INFO) << "Placed " << entities()->getMaxId() << " entities!"
              << std::endl;
    events()->fire<MapGeneratedEvent>();
}