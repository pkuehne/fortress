#ifndef __GENERATOR_H__
#define __GENERATOR_H__

typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int rooms;
} GEN_PARAMS;

void generateDungeon (GEN_PARAMS params);

#endif
