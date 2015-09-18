#include "graphics_interface.h"
#include <gmock/gmock.h>

class GraphicsMock : public GraphicsInterface {
public:
    MOCK_METHOD2 (initialise, void (int argc, char** argv));
    MOCK_METHOD0 (spin, void ());
    MOCK_METHOD0 (beginScreenUpdate, void ());
    MOCK_METHOD0 (endScreenUpdate, void ());

    MOCK_METHOD0 (getScreenHeight, int());
    MOCK_METHOD0 (getScreenWidth, int () );
    MOCK_METHOD2 (updateScreenSize, void  (int width, int height) );


    MOCK_METHOD5 (drawString, void (int y, int x, const char* s, Color fg, Color bg));
    MOCK_METHOD5 (drawTile, void (int y, int x, unsigned int tile, Color fg, Color bg));
    MOCK_METHOD4 (drawBorder, void (int y, int x, int height, int width));
    MOCK_METHOD4 (clearArea, void  (int y, int x, int height, int width) );
    MOCK_METHOD4 (calculateWindowOffsetsFromCentre, void  (int height, int width, int& y, int& x) );

    MOCK_METHOD1 (setKeyboardFunc, void (KeyboardFuncPtr func));
    MOCK_METHOD1 (setKeyboardUpFunc, void  (KeyboardFuncPtr func));
    MOCK_METHOD1 (setDisplayFunc, void (DisplayFuncPtr func));
    MOCK_METHOD1 (setMouseFunc, void (MouseFuncPtr func));
    MOCK_METHOD1 (setResizeFunc, void  (ResizeFuncPtr func));


};
