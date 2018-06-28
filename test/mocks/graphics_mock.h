#ifndef __GRAPHICS_MOCK_H__
#define __GRAPHICS_MOCK_H__

#include "../../src/core/graphics.h"
#include <gmock/gmock.h>

class GraphicsMock : public Graphics {
public:
    MOCK_METHOD5(drawTile,
                 void(int y, int x, unsigned int tile, Color fg, Color bg));
    MOCK_METHOD5(drawString,
                 unsigned int(int y, int x, const char* s, Color fg, Color bg));
    MOCK_METHOD4(drawBorder, void(int y, int x, int height, int width));
};

#endif
