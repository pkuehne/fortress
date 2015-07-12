#ifndef WINDOW_MOCK_H
#define WINDOW_MOCK_H

#include "window_interface.h"
#include <gmock/gmock.h>

class WindowMock : public WindowInterface {
public:
     MOCK_METHOD1 (initialise, void (GameEngineInterface* a_engine));
     MOCK_METHOD0 (destroy, void (void));

     MOCK_METHOD0 (getEngine, GameEngineInterface* ());
     MOCK_METHOD1 (keyDown, void (unsigned char key));
     MOCK_METHOD1 (keyUp, void (unsigned char key));
     MOCK_METHOD1 (getKey, bool (unsigned char key));
     MOCK_METHOD3 (mouseDown, void (int x, int y, int button));
     MOCK_METHOD3 (mouseUp, void (int x, int y, int button));
     MOCK_METHOD0 (beforeRedraw, void (void));
     MOCK_METHOD0 (redraw, void (void));
     MOCK_METHOD0 (afterRedraw, void (void));
     MOCK_METHOD2 (resize, void (int width, int height));
};

#endif
