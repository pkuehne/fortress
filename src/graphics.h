#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "color.h"

void setup_graphics ();
void start_graphics ();

unsigned char* loadImage (const char* filename);
void drawString (int y, int x, const char* s);
void drawTile (int y, int x, unsigned int tile, Color fg, Color bg);
void drawBorder (int y, int x, int height, int width);

void beginScreenUpdate();
void endScreenUpdate();

typedef enum {
    ICON_BRICK = 247,
    ICON_MAX = 12*48
} ICON_TYPE;

#endif
