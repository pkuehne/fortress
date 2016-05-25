#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "game_engine_interface.h"
#include "graphics_interface.h"
#include "entity_manager_interface.h"
#include "window_manager_interface.h"
#include "game_system_interface.h"
#include "event_manager_interface.h"
#include "map_manager_interface.h"
#include "component_manager.h"
#include "entity_manager_interface.h"
#include "location.h"

#include <string>
#include <vector>
#include <cstdlib>


class GameEngine : public GameEngineInterface {
public:
    GameEngine (GraphicsInterface* a_graphics);
    ~GameEngine ();

    void initialise (void);
    void tick (void);

    void quit() { m_graphics->terminate(); }
    bool isPlayerTurn() { return m_playerTurn; }
    void swapTurn();
    unsigned int getTurn() { return m_turn; }
    void setTurn (unsigned int turn) { m_turn = turn; }

    void raiseEvent (Event* event) { m_eventManager->raiseEvent (event); }

    unsigned long long getTick() { return m_tick; }

    GraphicsInterface* getGraphics() { return m_graphics; }

    void setEntityManager (EntityManagerInterface* a_manager) { m_entityManager = a_manager; }
    void setWindowManager (WindowManagerInterface* a_manager) { m_windowManager = a_manager; }
    void setEventManager (EventManagerInterface* a_manager) { m_eventManager = a_manager; }
    void setMapManager (MapManagerInterface* a_manager) { m_mapManager = a_manager; }
    EntityManagerInterface* getEntities() { return m_entityManager; }
    WindowManagerInterface* getWindows() { return m_windowManager; }
    ComponentManager* getComponents() { return m_componentManager; }
    MapManagerInterface* getMap() { return m_mapManager; }

    void addSystem (GameSystemInterface* a_system) { m_systems.push_back(a_system); }

    void addMessage (const Message& message) { m_messages.push_back (message); }
    void addMessage (const MessageType&, const std::string& message);
    std::vector<Message>& getMessages() { return m_messages; }

    void setArea (unsigned int area) { m_mapManager->setArea (area); }
    unsigned int getArea() { return m_mapManager->getArea(); }

    // New style interfaces
    EntityId player() { return m_entityManager->getPlayer(); }

    //const Location& location (EntityId entity) { return m_entityManager->getLocation(entity); }
    Location location (EntityId entity) { return m_entityManager->getLocation(entity); }
    const EntityHolder& entities (unsigned int area = 0) { return m_entityManager->get(area); }
    EntityHolder entities (const Location& loc) { return m_mapManager->findEntitiesAt(loc); }

    Tile& tile (const Location& loc) { return m_mapManager->getTile (loc); }

private:
    unsigned long long  m_tick;
    bool                m_playerTurn;
    unsigned int        m_turn;

    EntityManagerInterface* m_entityManager;
    EventManagerInterface*  m_eventManager;
    WindowManagerInterface* m_windowManager;
    ComponentManager*       m_componentManager;
    MapManagerInterface*    m_mapManager;

    std::vector<GameSystemInterface*>   m_systems;

    GraphicsInterface*      m_graphics;

    std::vector<Message>    m_messages;
    unsigned int            m_depth = 0;
    unsigned int            m_area = 0;
};

#endif
