#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <cstring>
#include "window_interface.h"

class GameEngineInterface;

class Window : public WindowInterface
{
public:
    static const int MAX_BUTTONS = 5;

    Window(): m_engine(0) { memset (ascii_keys, false, sizeof(ascii_keys)); }
    virtual ~Window() { }
    virtual void initialise (GameEngineInterface* a_engine, void* Args = 0, void* Retval = 0);
    virtual void destroy (void);
    virtual void setDimensions (int x, int y, int width, int height);
    virtual void setTitle (const std::string& title) { m_title = title; }
    virtual std::string getTitle () { return m_title; }
    virtual int getXOffset() { return m_xOffset; }
    virtual int getYOffset() { return m_yOffset; }
    virtual int getWidth() { return m_width; }
    virtual int getHeight() { return m_height; }
    virtual void resize() { setDimensions (m_xOffset, m_yOffset, m_width, m_height); }
    virtual void update() { }

    virtual unsigned int drawString (int y, int x, const char* text, Color fg = Color(WHITE), Color bg = Color(BLACK));
    virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg);
    virtual void drawBorder (int y, int x, int height, int width);
    virtual void clearArea (int y, int x, int height, int width);

    virtual GameEngineInterface* getEngine() { return m_engine; }
    virtual void keyDown (unsigned char key) { ascii_keys[key] = true; }
    virtual void keyUp (unsigned char key) { ascii_keys[key] = false; }
    virtual bool getKey (unsigned char key) { return ascii_keys[key]; }
    virtual void mouseDown (int x, int y, int button);
    virtual void mouseUp (int x, int y, int button);
    virtual bool getMouseButton (int button);
    virtual void beforeRedraw();
    virtual void redraw () { };
    virtual void afterRedraw();
    virtual void resize (int width, int height);
    virtual void* getArgs() { return m_args; }
    virtual void* getRetval() { return m_retval; }

    virtual void gainFocus() { };
    virtual void loseFocus() { };

    virtual void drawProgress (unsigned int x, unsigned int y, unsigned int value, unsigned int max);
    virtual unsigned int wrapText (const std::string& text, std::vector<std::string>& lines, unsigned int maxWidth, unsigned int maxRows);
    
private:
    bool                    ascii_keys[256];
    bool                    special_keys[256];
    int                     m_buttons[MAX_BUTTONS];
    GameEngineInterface*    m_engine;
    void*                   m_args;
    void*                   m_retval;
    int                     m_xOffset;
    int                     m_yOffset;
    int                     m_width;
    int                     m_height;
    std::string             m_title;
};

#endif
