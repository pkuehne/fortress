#pragma once

#include <cstring>
#include <memory>

class EntityManager;
class MapManager;
class ComponentManager;
class EventManager;

class GeneratorInterface {
public:
    GeneratorInterface() : m_mapCache(0) {}
    virtual ~GeneratorInterface() {}
    virtual bool generate() = 0;
    virtual void createEntitiesFromMap() = 0;

    virtual void initialise(std::shared_ptr<EventManager> events,
                            std::shared_ptr<ComponentManager> components,
                            std::shared_ptr<EntityManager> entities,
                            std::shared_ptr<MapManager> map) {
        m_events = events;
        m_components = components;
        m_entities = entities;
        m_map = map;
    }
    virtual void reset() {
        if (m_mapCache) {
            delete[] m_mapCache;
            m_mapCache = 0;
        }
    }
    virtual void initMap(unsigned char tile) {
        reset();
        m_mapCache = new unsigned char[m_mapHeight * m_mapWidth];
        memset(m_mapCache, tile, m_mapHeight * m_mapWidth);
    }

    unsigned char& getByCoordinate(unsigned int x, unsigned int y) {
        return getByIndex(CoordToIndex(x, y));
    }
    unsigned char& getByIndex(unsigned int index) { return m_mapCache[index]; }

    bool isValidIndex(unsigned int index) {
        return (index > 0 && index < sizeof(m_mapCache));
    }
    bool isValidCoordinate(unsigned int x, unsigned int y) {
        return (x < m_mapWidth && y < m_mapHeight);
    }
    int CoordToIndex(unsigned int x, unsigned int y) {
        return y * m_mapWidth + x;
    }
    void IndexToCoord(unsigned int index, unsigned int& x, unsigned int& y) {
        x = index % m_mapWidth;
        y = (index - x) / m_mapWidth;
    }

    virtual unsigned int& mapHeight() { return m_mapHeight; }
    virtual unsigned int& mapWidth() { return m_mapWidth; }
    virtual unsigned int& area() { return m_area; }

protected:
    std::shared_ptr<ComponentManager> components() const {
        return m_components;
    }
    std::shared_ptr<EntityManager> entities() const { return m_entities; }
    std::shared_ptr<EventManager> events() const { return m_events; }
    std::shared_ptr<MapManager> map() const { return m_map; }

private:
    unsigned char* m_mapCache = nullptr;

protected:
    unsigned int m_area = 0;
    unsigned int m_mapWidth = 0;
    unsigned int m_mapHeight = 0;

private:
    std::shared_ptr<EventManager> m_events = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<MapManager> m_map = nullptr;
};
