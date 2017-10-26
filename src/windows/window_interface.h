#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

#include <string>
#include "../core/color.h"
#include <vector>

class GameEngineInterface;

class WindowInterface {
public:
    virtual ~WindowInterface() {}
    virtual void initialise (GameEngineInterface* a_engine, void* Args = 0, void* Retval = 0) = 0;
    virtual void destroy (void) = 0;
    virtual void setDimensions (int x, int y, int width, int height) = 0;
    virtual void setTitle (const std::string& title) = 0;
    virtual std::string getTitle () = 0;
    virtual int getXOffset() = 0;
    virtual int getYOffset() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    virtual unsigned int drawString (int y, int x, const char* text, Color fg = Color(WHITE), Color bg = Color(BLACK)) = 0;
    virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg) = 0;
    virtual void drawBorder (int y, int x, int height, int width) = 0;
    virtual void clearArea (int y, int x, int height, int width) = 0;

    virtual GameEngineInterface* getEngine() = 0;
    virtual void keyDown (unsigned char key) = 0;
    virtual void keyUp (unsigned char key) = 0;
    virtual bool getKey (unsigned char key) = 0;
    virtual void mouseDown (int x, int y, int button) = 0;
    virtual void mouseUp (int x, int y, int button) = 0;
    virtual void beforeRedraw() = 0;
    virtual void redraw () = 0;
    virtual void renderWidgets () = 0;
    virtual void afterRedraw() = 0;
    virtual void resize (int width, int height) = 0;
    virtual void resize() = 0;
    virtual void update() = 0;

    virtual void* getArgs() = 0;
    virtual void* getRetval() = 0;

    virtual void gainFocus() = 0;
    virtual void loseFocus() = 0;

    virtual void drawProgress (unsigned int x, unsigned int y, unsigned int value, unsigned int max) = 0;
    virtual unsigned int wrapText (const std::string& text, std::vector<std::string>& lines, unsigned int maxWidth, unsigned int maxRows) = 0;
};

#endif
