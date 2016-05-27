#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "location.h"
#include "entity_manager.h"
#include "map_manager.h"
#include "component_manager.h"

class Tile;

typedef enum {
    INFO    = 0,
    GOOD    = 1,
    WARN    = 2,
    CRIT    = 3
} MessageType;

typedef struct {
    MessageType severity;
    std::string message;
} Message;

typedef unsigned long long tick_t;

class GameState {
    public:
        GameState ( MapManager* map = new MapManager(),
                    EntityManager* entities = new EntityManager(),
                    ComponentManager* components = new ComponentManager());

        bool isPlayerTurn() { return m_playerTurn; }
        void nextTurn() { m_turn++; m_playerTurn = !m_playerTurn; }
        tick_t getTurn() { return m_turn; }

        MapManager* map();
        EntityManager* entityManager();
        ComponentManager* components();

        Tile& tile (const Location&);
        bool isValidTile (const Location&);

        const EntityHolder& entities ();
        EntityHolder entities (const Location& loc);

        Location location (EntityId entity);
        Location location (const Location&, Direction direction);

        EntityId player();
        EntityId createEntity(Location&);

        void setArea (unsigned int area);
        unsigned int getArea();

        void save (const std::string& filename);
        void load (const std::string& filename);

        void addMessage (const Message& message);
        void addMessage (const MessageType&, const std::string& message);
        std::vector<Message>& getMessages();

    private:
        bool                m_playerTurn = true;
        tick_t              m_turn = 0;
        MapManager*         m_map = 0;
        EntityManager*      m_entities = 0;
        ComponentManager*   m_components = 0;
        std::vector<Message>    m_messages;
};

#endif
