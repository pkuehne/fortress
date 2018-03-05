#pragma once

#include "widget.h"

class Frame : public Widget
{
  public:
    Widget *setWindowOffsets(unsigned int x, unsigned int y);
    Widget *realignWidget(unsigned int width, unsigned int height);
    void render();
    void keyPress(unsigned char key);
};