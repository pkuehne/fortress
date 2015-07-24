#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "color.h"
#include "graphics_interface.h"
#include "config_manager.h"

class Graphics : public GraphicsInterface {
public:
    virtual void initialise(int argc, char** argv);
    virtual void spin();

    virtual void drawString (int y, int x, const char* s);
    virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg);
    virtual void drawBorder (int y, int x, int height, int width);

    virtual void beginScreenUpdate();
    virtual void endScreenUpdate();

    virtual void setKeyboardFunc (KeyboardFuncPtr func);
    virtual void setKeyboardUpFunc (KeyboardFuncPtr func);
    virtual void setDisplayFunc (DisplayFuncPtr func);
    virtual void setMouseFunc (MouseFuncPtr func);

private:
    ConfigManager   m_config;
};

void start_graphics ();

typedef enum {
    ICON_BRICK = 247,
    ICON_MAX = 12*48
} ICON_TYPE;

#endif
