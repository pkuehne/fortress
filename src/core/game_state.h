#pragma once

#include "color.h"
#include "component_manager.h"
#include "entity_manager.h"
#include "location.h"
#include "map_manager.h"
#include "prefab_builder.h"
#include "quest.h"

class Tile;

typedef enum { INFO = 0, GOOD = 1, WARN = 2, CRIT = 3 } MessageType;

typedef struct {
    MessageType severity;
    std::string message;
    Color getColor() {
        switch (severity) {
            case INFO:
                return Color(WHITE);
            case GOOD:
                return Color(GREEN);
            case WARN:
                return Color(YELLOW);
            case CRIT:
            default:
                return Color(RED);
        }
    }
} Message;

struct Debug {
    bool showNpcPaths = false;
};

typedef unsigned long long tick_t;

class GameState {
public:
    GameState(MapManager* map = new MapManager(),
              EntityManager* entities = new EntityManager(),
              ComponentManager* components = new ComponentManager());
    virtual ~GameState() {}

    bool isPlayerTurn() { return m_playerTurn; }
    void nextTurn() {
        m_turn++;
        m_playerTurn = !m_playerTurn;
    }
    tick_t turn() { return m_turn; }

    MapManager* map();
    EntityManager* entityManager();
    ComponentManager* components();

    Debug& debug() { return m_debug; }

    Tile& tile(const Location&);
    virtual bool isValidTile(const Location&);

    virtual const EntityHolder& entities();
    virtual EntityHolder entities(const Location& loc);

    Location location(EntityId entity);
    Location location(const Location&, Direction direction);

    EntityId player();
    EntityId createEntity(Location&);

    PrefabBuilder& prefabs() { return m_prefabs; }

    void setArea(unsigned int area);
    unsigned int getArea();

    void save(const std::string& filename);
    // void load(const std::string& filename);

    void addMessage(const Message& message);
    void addMessage(const MessageType&, const std::string& message);
    std::vector<Message>& getMessages();

    std::vector<Quest*>& getQuests() { return m_quests; }

private:
    bool m_playerTurn = true;
    tick_t m_turn = 0;
    MapManager* m_map = nullptr;
    EntityManager* m_entities = nullptr;
    ComponentManager* m_components = nullptr;
    PrefabBuilder m_prefabs;

    std::vector<Message> m_messages;
    Debug m_debug;
    std::vector<Quest*> m_quests;
};
