#pragma once

#include "../../src/windows/widget.h"
#include <gmock/gmock.h>

class WidgetMock : public Widget
{
  public:
    MOCK_METHOD2(setWindowOffsets, Widget *(unsigned int x, unsigned int y));
    MOCK_METHOD2(realignWidget, Widget *(unsigned int w, unsigned int h));
    MOCK_METHOD0(render, void());
    MOCK_METHOD1(keyPress, void(unsigned char key));
};