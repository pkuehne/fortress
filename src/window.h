#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "graphics.h"

class Window
{
public:
    Window() { }
    virtual ~Window() { }
    virtual void initialise (void);
    virtual void destroy (void);

    virtual void keyDown (unsigned char key) { ascii_keys[key] = true; }
    virtual void keyUp (unsigned char key) { ascii_keys[key] = false; }
    virtual bool getKey (unsigned char key) { return ascii_keys[key]; }
    virtual void mouseDown (int x, int y, int button);
    virtual void mouseUp (int x, int y, int button);
    virtual void beforeRedraw() { beginScreenUpdate(); }
    virtual void redraw () = 0;
    virtual void afterRedraw() { endScreenUpdate(); }
    virtual void resize (int width, int height);

private:
    bool ascii_keys[256];
    bool special_keys[256];
};

#endif
