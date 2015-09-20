#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "color.h"
#include "graphics_interface.h"
#include "config_manager.h"
#include <GLFW/glfw3.h>

class Graphics : public GraphicsInterface {
public:
    virtual void initialise(int argc, char** argv);
    virtual void spin();

    virtual unsigned int drawString (int y, int x, const char* s, Color fg = Color(WHITE), Color bg = Color(BLACK));
    virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg);
    virtual void drawBorder (int y, int x, int height, int width);
    virtual void clearArea (int y, int x, int height, int width);
    virtual void calculateWindowOffsetsFromCentre (int height, int width, int& y, int& x);
    virtual void terminate() { glfwDestroyWindow(m_window); }

    virtual void beginScreenUpdate();
    virtual void endScreenUpdate();

    virtual int getScreenHeight();
    virtual int getScreenWidth();

    virtual void updateScreenSize (int width, int height);

    virtual void setKeyDownFunc (KeyboardFuncPtr func);
    virtual void setKeyUpFunc (KeyboardFuncPtr func);
    virtual void setDisplayFunc (DisplayFuncPtr func);
    virtual void setMouseFunc (MouseFuncPtr func);
    virtual void setResizeFunc (ResizeFuncPtr func);

    virtual void callResizeFunc (int width, int height);
    virtual void callKeyboardFunc (int key, int scancode, int action, int mods);

private:
    ConfigManager       m_config;
    int                 m_width;
    int                 m_height;
    GLFWwindow*         m_window;
    DisplayFuncPtr      m_displayFunc;
    ResizeFuncPtr       m_resizeFunc;
    KeyboardFuncPtr     m_keyDownFunc;
    KeyboardFuncPtr     m_keyUpFunc;
};

void start_graphics ();

typedef enum {
    ICON_BRICK = 247,
    ICON_MAX = 12*48
} ICON_TYPE;

#endif
