#ifndef GENERATOR_H
#define GENERATOR_H

#include "generator_interface.h"

class Generator : public GeneratorInterface {
public:
    void initialise (GameEngineInterface* a_engine) { m_engine = a_engine; }
    void generate();

    unsigned int& mapHeight() { return m_mapHeight; }
    unsigned int& mapWidth() { return m_mapWidth; }
    unsigned int& numberOfRooms() { return m_rooms; }

private:
    bool generateRoom (char* map);
    void loadMap (char* map);

private:
    GameEngineInterface*    m_engine;
    unsigned int            m_mapHeight;
    unsigned int            m_mapWidth;
    unsigned int            m_rooms;
};

#endif
