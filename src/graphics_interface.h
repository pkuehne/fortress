#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H

#include "color.h"


typedef void (*KeyboardFuncPtr) (unsigned char key, int x, int y);
typedef void (*DisplayFuncPtr) (void);
typedef void (*MouseFuncPtr) (int button, int state, int x, int y);

class GraphicsInterface {
public:
    virtual ~GraphicsInterface() {}
    virtual void initialise (int argc, char** argv) = 0;
    virtual void spin() = 0;
    virtual void beginScreenUpdate() = 0;
    virtual void endScreenUpdate() = 0;

    virtual void drawString (int y, int x, const char* s) = 0;
    virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg) = 0;
    virtual void drawBorder (int y, int x, int height, int width) = 0;

    virtual void setKeyboardFunc (KeyboardFuncPtr func) = 0;
    virtual void setKeyboardUpFunc (KeyboardFuncPtr func) = 0;
    virtual void setDisplayFunc (DisplayFuncPtr func) = 0;
    virtual void setMouseFunc (MouseFuncPtr func) = 0;
private:

};

#endif
