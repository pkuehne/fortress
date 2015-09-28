#ifndef RURAL_GENERATOR
#define RURAL_GENERATOR

#include "generator_interface.h"

class RuralGenerator : public GeneratorInterface {
public:
    RuralGenerator() : m_map (0) { }
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    bool generate();
    void createEntitiesFromMap();
    void reset ();

    unsigned int& mapHeight() { return m_mapHeight; }
    unsigned int& mapWidth() { return m_mapWidth; }

    bool isValid (unsigned int x, unsigned int y) { return (x >= 0 && x < m_mapWidth && y >= 0 && y < m_mapHeight); }
    void placeWoods();
    void placePlayer();

private:
    GameEngineInterface*    m_engine;
    unsigned int            m_mapHeight;
    unsigned int            m_mapWidth;
    unsigned char*          m_map;
};

#endif
