#include "entity_manager.h"
#include "../components/game_component.h"
#include "event_manager.h"
#include "location.h"
#include <climits>
#include <flecs.h>
#include <fstream>
#include <iostream>

void EntityManager::initialise(std::shared_ptr<EventManager> events) {
    m_events = events;

    spdlog::info("Enabling REST access");
    world().set<flecs::Rest>({});
    world().import <flecs::monitor>(); // Collect statistics periodically

    spdlog::info("Registering custom handlers");
    // Register reflection for std::string
    world()
        .component<std::string>()
        .opaque(flecs::String) // Opaque type that maps to string
        .serialize([](const flecs::serializer* s, const std::string* data) {
            const char* str = data->c_str();
            return s->value(flecs::String, &str); // Forward to serializer
        })
        .assign_string([](std::string* data, const char* value) {
            *data = value; // Assign new value to std::string
        });

    spdlog::info("Assigning GameResource");
    world().set<GameComponent>({
        world().timer("SimTimer").interval(0.5f).disable() // sim_speed, start
                                                           // disabled
    });
    flecs::entity TurnPhase = world().entity("TurnPhase").add(flecs::Phase);
    TurnPhase.add(flecs::DependsOn, flecs::OnUpdate);
    TurnPhase.disable();

    // world().observer<flecs::Phase>("TurnEvent Observer")
    //     .event<TurnEvent>()
    //     .iter([&TurnPhase](flecs::iter& it) { TurnPhase.enable(); });

    world()
        .system("EndTurn")
        .kind(flecs::PreUpdate)
        .iter([&TurnPhase](flecs::iter& it) {
            it.world().lookup("TurnPhase").disable();
        });

    world().system("Turn-based").kind(TurnPhase).iter([](flecs::iter& it) {
        spdlog::info("Turn happened in the ECS");
    });
}

EntityId EntityManager::createEntity(const Location& location) {
    EntityId l_entity = world().entity().id();

    addEntity(l_entity, location);
    return l_entity;
}

void EntityManager::addEntity(EntityId id, const Location& location) {
    if (id >= m_maxId) {
        m_maxId = id + 1;
    }
    m_locations[id] = location;
    m_entities[location.area].insert(id);
    m_allEntities.insert(id);

    assert(world().entity(id).id() == id);
    m_events->fire<AddEntityEvent>(id, location);
}

void EntityManager::destroyEntity(EntityId id) {
    const Location& location = m_locations[id];

    if (location.isValid()) {
        m_entities[m_locations[id].area].erase(id);
    }
    m_locations.erase(id);
    m_allEntities.erase(id);
}

void EntityManager::setLocation(EntityId entity, const Location& location) {
    if (!entity) {
        return;
    }
    if (m_locations[entity].isValid()) {
        m_entities[location.area].erase(entity);
    }
    Location prev = m_locations[entity];
    m_locations[entity] = location;
    if (m_locations[entity].isValid()) {
        m_entities[location.area].insert(entity);
    }
    m_events->fire<ChangeLocationEvent>(entity, prev, location);
}
