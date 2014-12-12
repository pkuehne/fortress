#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

void setup_graphics ();
void start_graphics ();

unsigned char* loadImage (const char* filename);
void printString (int x, int y, const char* s);
void drawImage (int x, int y, const unsigned char* image);

#endif
