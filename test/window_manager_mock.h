#ifndef WINDOW_MANAGER_MOCK_H
#define WINDOW_MANAGER_MOCK_H

#include "window_manager_interface.h"
#include <gmock/gmock.h>

class WindowManagerMock : public WindowManagerInterface {
public:
     MOCK_METHOD1 (initialise, void (GameEngineInterface* engine));
     MOCK_METHOD1 (pushWindow, void (WindowInterface* win));
     MOCK_METHOD0 (popWindow, void ());
     MOCK_METHOD1 (replaceWindow, void (WindowInterface* win));
     MOCK_METHOD0 (getActive, WindowInterface* ());

};

#endif
