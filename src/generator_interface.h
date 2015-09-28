#ifndef GENERATOR_INTERFACE_H
#define GENERATOR_INTERFACE_H

class GameEngineInterface;

class GeneratorInterface {
public:
    GeneratorInterface() : m_map(0) { }
    virtual ~GeneratorInterface() { }
    virtual bool generate() = 0;
    virtual void createEntitiesFromMap() = 0;

    virtual void initialise (GameEngineInterface* engine) { m_engine = engine; }
    virtual void reset () {
        if (m_map) {
            delete[] m_map;
            m_map = 0;
        }
    }

    unsigned char& getByCoordinate (unsigned int x, unsigned int y) { return getByIndex (CoordToIndex(x,y)); }
    unsigned char& getByIndex (unsigned int index) { return m_map[index]; }

    bool isValidIndex (unsigned int index) { return (index > 0 && index < sizeof (m_map)); }
    bool isValidCoordinate (unsigned int x, unsigned int y) { return (x>=0 && x<m_mapWidth && y>=0 && y<m_mapHeight); }
    int CoordToIndex (unsigned int x, unsigned int y) { return y * m_mapWidth + x; }
    void IndexToCoord (unsigned int index, unsigned int& x, unsigned int& y) { x = index%m_mapWidth; y = (index-x)/m_mapWidth; }

    virtual unsigned int& mapHeight() { return m_mapHeight; }
    virtual unsigned int& mapWidth() { return m_mapWidth; }

private:
    unsigned char*          m_map;
    unsigned int            m_mapWidth;
    unsigned int            m_mapHeight;
protected:
    GameEngineInterface*    m_engine;
};

#endif
