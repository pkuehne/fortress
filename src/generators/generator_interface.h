#ifndef GENERATOR_INTERFACE_H
#define GENERATOR_INTERFACE_H

#include <cstring>

class GameEngine;

class GeneratorInterface {
public:
    GeneratorInterface() : m_map(0) {}
    virtual ~GeneratorInterface() {}
    virtual bool generate() = 0;
    virtual void createEntitiesFromMap() = 0;

    virtual void initialise(GameEngine* engine) { m_engine = engine; }
    virtual void reset() {
        if (m_map) {
            delete[] m_map;
            m_map = 0;
        }
    }
    virtual void initMap(unsigned char tile) {
        reset();
        m_map = new unsigned char[m_mapHeight * m_mapWidth];
        memset(m_map, tile, m_mapHeight * m_mapWidth);
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
    GameEngine* m_engine = nullptr;
};

#endif
