#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "game_engine_interface.h"
#include "graphics_interface.h"
#include "entity_manager_interface.h"
#include "window_manager_interface.h"
#include "game_system_interface.h"
#include "event_manager_interface.h"
#include "generator_interface.h"

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
    void swapTurn() { m_playerTurn = !m_playerTurn; m_turn++; }
    unsigned int getTurn() { return m_turn; }

    void raiseEvent (Event* event) { m_eventManager->raiseEvent (event); }
    EntityManagerInterface* getEntities() { return m_entityManager; }
    ComponentManager* getComponents() { return m_componentManager; }

    void loadMap (unsigned int width, unsigned int height);

    unsigned long long getTick() { return m_tick; }
    WindowManagerInterface* getWindows() { return m_windowManager; }

    GraphicsInterface* getGraphics() { return m_graphics; }

    void setEntityManager (EntityManagerInterface* a_manager) { m_entityManager = a_manager; }
    void setWindowManager (WindowManagerInterface* a_manager) { m_windowManager = a_manager; }
    void setEventManager (EventManagerInterface* a_manager) { m_eventManager = a_manager; }

    void addSystem (GameSystemInterface* a_system) { m_systems.push_back(a_system); }
    void setGenerator (GeneratorInterface* a_generator) { m_generator = a_generator; }

    void addMessage (const Message& message) { m_messages.push_back (message); }
    void addMessage (const MessageType&, const std::string& message);
    std::vector<Message>& getMessages() { return m_messages; }


    void setLevel (unsigned int level) { m_level = level; }
    unsigned int getLevel () { return m_level; }

    void setMaxLevel (unsigned int maxLevel) { m_maxLevel = maxLevel; }
    unsigned int getMaxLevel () { return m_maxLevel; }

    unsigned int getArea () { return m_currentArea; }
    void setArea (unsigned int area) { m_currentArea = area; }

    Tile& getTile (unsigned int x, unsigned int y, unsigned int z) { return getTile (map2index (x, y, z)); }
    Tile& getTile (const Location& location) { return getTile (location.x, location.y, location.z); }
    Tile& getTile (unsigned int index) { return m_map[index]; }

    int map2index (unsigned int x, unsigned int y, unsigned int z) { return (z-1)*m_mapHeight*m_mapWidth + y*m_mapHeight + x; }
    void index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z) {
        x = index%m_mapWidth;
        y = (index-x)/m_mapHeight;
        z = (index-(y*m_mapWidth)+x) / (m_mapHeight*m_mapWidth) + 1;
    }
    bool isValidTile (unsigned int x, unsigned int y, unsigned int z) { return (x>=0 && x<m_mapWidth && y>=0 && y<m_mapHeight && z>0 && z<=m_maxLevel); }
    bool isValidTile (unsigned int index) { return (index > 0 && index < sizeof (m_map)); }

    unsigned int getMapHeight() { return m_mapHeight; }
    unsigned int getMapWidth() { return m_mapWidth; }

private:
    unsigned long long  m_tick;
    bool                m_playerTurn;
    unsigned int        m_turn;

    EntityManagerInterface* m_entityManager;
    EventManagerInterface*  m_eventManager;
    WindowManagerInterface* m_windowManager;
    ComponentManager*       m_componentManager;

    std::vector<GameSystemInterface*>   m_systems;

    GraphicsInterface*      m_graphics;
    GeneratorInterface*     m_generator;

    std::vector<Message>    m_messages;
    unsigned int            m_level;
    unsigned int            m_maxLevel;
    unsigned int            m_currentArea;

    unsigned int            m_mapWidth;
    unsigned int            m_mapHeight;
    Tile*                   m_map;
};

#endif