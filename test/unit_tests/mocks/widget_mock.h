#pragma once

#include "../../src/widgets/widget.h"
#include <gmock/gmock.h>

class WidgetMock : public Widget {
public:
    MOCK_METHOD4(realign, void(unsigned int x, unsigned int y, unsigned int w,
                               unsigned int h));
    MOCK_METHOD0(render, void());
    MOCK_METHOD1(keyPress, void(unsigned char key));
};