#pragma once

#include "color.h"
#include "component_manager.h"
#include "entity_manager.h"
#include "location.h"
#include "map_manager.h"
#include "quest.h"
#include <memory>

class Tile;
class WorldInfo;

struct Debug {
    bool showNpcPaths = false;
    bool revealAllTiles = false;
};

typedef unsigned long long tick_t;

class GameState {
public:
    GameState(MapManager* map = new MapManager(),
              EntityManager* entities = new EntityManager(),
              ComponentManager* components = new ComponentManager());
    virtual ~GameState();

    bool isPlayerTurn() { return m_playerTurn; }
    void nextTurn() {
        m_turn++;
        m_playerTurn = !m_playerTurn;
    }
    tick_t turn() { return m_turn; }

    virtual MapManager* map();
    virtual EntityManager* entityManager();
    virtual ComponentManager* components();

    Debug& debug() { return m_debug; }

    virtual Tile& tile(const Location&);
    virtual bool isValidTile(const Location&);

    virtual const EntityHolder& entities();
    virtual const EntityHolder& entities(const Location& loc);
    virtual const EntityHolder& entitiesInArea(unsigned int area);

    Location location(EntityId entity);
    Location location(const Location&, Direction direction);

    virtual EntityId player();
    EntityId createEntity(const Location&);

    std::vector<Quest*>& getQuests() { return m_quests; }

    /// @brief Provides access to the world information
    WorldInfo& world();

private:
    bool m_playerTurn = true;
    tick_t m_turn = 0;
    MapManager* m_map = nullptr;
    EntityManager* m_entities = nullptr;
    ComponentManager* m_components = nullptr;
    std::shared_ptr<WorldInfo> m_world;

    Debug m_debug;
    std::vector<Quest*> m_quests;
};
