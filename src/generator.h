#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "game_engine_interface.h"

typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int rooms;
} GEN_PARAMS;

void generateDungeon (GameEngineInterface* a_engine, GEN_PARAMS params);

#endif
