#pragma once

#include "../core/entity.h"
#include "../core/game_system_base.h"
#include <string>
#include <vector>

class Location;

class GeneratorInterface : public GameSystemBase {
public:
    GeneratorInterface() : m_map(0) {}
    virtual ~GeneratorInterface() {}
    virtual bool generate() = 0;
    virtual void createEntitiesFromMap() = 0;
    virtual void reset() {
        if (m_map) {
            delete[] m_map;
            m_map = 0;
        }
    }
    virtual void initMap(unsigned char tile) {
        reset();
        m_map = new unsigned char[m_mapHeight * m_mapWidth]();
    }

    unsigned char& getByCoordinate(unsigned int x, unsigned int y) {
        return getByIndex(CoordToIndex(x, y));
    }
    unsigned char& getByIndex(unsigned int index) { return m_map[index]; }

    bool isValidIndex(unsigned int index) {
        return (index > 0 && index < sizeof(m_map));
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

private:
    unsigned char* m_map = nullptr;

protected:
    unsigned int m_area = 0;
    unsigned int m_mapWidth = 0;
    unsigned int m_mapHeight = 0;
};

class RuralGenerator : public GeneratorInterface {
public:
    void registerHandlers();
    bool generate();
    void reset();
    void createEntitiesFromMap();
    std::vector<EntityId>& getAreaLinks() { return m_areaLinks; }
    EntityId createPrefab(const std::string& type, Location& location);

private:
    void placeWoods();
    void placeDungeonStairs();
    void placeForester();
    void placePlayer();
    void placeApples();

private:
    std::vector<EntityId> m_areaLinks;
};
