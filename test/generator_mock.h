#ifndef GENERATOR_MOCK_H
#define GENERATOR_MOCK_H

#include <generator_interface.h>
#include <gmock/gmock.h>

class GeneratorMock : public GeneratorInterface {
public:
    MOCK_METHOD1(initialise, void (GameEngineInterface*) );
    MOCK_METHOD0(generate, void () );
    MOCK_METHOD0(createEntitiesFromMap, void ());

    MOCK_METHOD0(mapHeight, unsigned int& () );
    MOCK_METHOD0(mapWidth, unsigned int& () );
    MOCK_METHOD0(numberOfRooms, unsigned int& () );
};

#endif
