#pragma once

#include <memory>
#include <vector>

class GameEngine;
class Window;
class EventManager;
class EntityManager;
class ComponentManager;
class MapManager;
class GraphicsInterface;

class WindowManager {
public:
    virtual ~WindowManager() = default;

    virtual void registerHandlers();

    virtual void initialise(GameEngine* engine,
                            std::shared_ptr<GraphicsInterface> graphics,
                            std::shared_ptr<EventManager> events,
                            std::shared_ptr<ComponentManager> components,
                            std::shared_ptr<EntityManager> entities,
                            std::shared_ptr<MapManager> map);
    virtual void pushWindow(std::shared_ptr<Window> win);

    virtual void popWindow();
    virtual void popAllWindows();
    virtual std::shared_ptr<Window> getActive();
    virtual void resize();
    virtual void nextTick();
    virtual void nextTurn();

private:
    std::shared_ptr<ComponentManager> components() const {
        return m_components;
    }
    std::shared_ptr<EntityManager> entities() const { return m_entities; }
    std::shared_ptr<EventManager> events() const { return m_events; }
    std::shared_ptr<MapManager> map() const { return m_map; }
    std::shared_ptr<GraphicsInterface> graphics() const { return m_graphics; }
    virtual void removeWindow(std::shared_ptr<Window> win);

private:
    GameEngine* m_engine = nullptr;
    std::vector<std::shared_ptr<Window>> m_windows;
    std::shared_ptr<GraphicsInterface> m_graphics = nullptr;
    std::shared_ptr<EventManager> m_events = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<MapManager> m_map = nullptr;
};
