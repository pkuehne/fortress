#ifndef WINDOW_MOCK_H
#define WINDOW_MOCK_H

#include "window_interface.h"
#include <gmock/gmock.h>

class WindowMock : public WindowInterface {
public:
     MOCK_METHOD3 (initialise, void (GameEngineInterface* a_engine, void* Args, void* Retval));
     MOCK_METHOD0 (destroy, void (void));

     MOCK_METHOD4 (setDimensions, void (int x, int y, int width, int height) );
     MOCK_METHOD1 (setTitle, void (const std::string& title) );
     MOCK_METHOD0 (getTitle, std::string () );
     MOCK_METHOD0 (getXOffset, int () );
     MOCK_METHOD0 (getYOffset, int () );
     MOCK_METHOD0 (getWidth, int () );
     MOCK_METHOD0 (getHeight, int () );

     MOCK_METHOD5 (drawString, void (int y, int x, const char* text, Color fg, Color bg));
     MOCK_METHOD5 (drawTile, void (int y, int x, unsigned int tile, Color fg, Color bg));

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
     MOCK_METHOD0 (resize, void());

     MOCK_METHOD0 (getArgs, void* ());
     MOCK_METHOD0 (getRetval, void* ());

     MOCK_METHOD0 (gainFocus, void ());
     MOCK_METHOD0 (loseFocus, void ());

};

#endif
