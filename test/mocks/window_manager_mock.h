#pragma once

#include "../../src/core/window_manager.h"
#include <gmock/gmock.h>

class WindowManagerMock : public WindowManager {
public:
    MOCK_METHOD1(registerWindow, void(std::shared_ptr<Window>));
};