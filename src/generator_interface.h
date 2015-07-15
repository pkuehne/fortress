#ifndef GENERATOR_INTERFACE_H
#define GENERATOR_INTERFACE_H

class GameEngineInterface;

class GeneratorInterface {
public:
    virtual ~GeneratorInterface() { }
    virtual void initialise (GameEngineInterface*) = 0;
    virtual void generate() = 0;

    virtual unsigned int& mapHeight() = 0;
    virtual unsigned int& mapWidth() = 0;
    virtual unsigned int& numberOfRooms() = 0;
};

#endif
