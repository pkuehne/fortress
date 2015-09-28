#ifndef RURAL_GENERATOR
#define RURAL_GENERATOR

#include "generator_interface.h"

class RuralGenerator : public GeneratorInterface {
public:
    bool generate();
    void reset();
    void createEntitiesFromMap();

    void placeWoods();
    void placePlayer();

private:
};

#endif
