#ifndef __SPLASH_WINDOW_H__
#define __SPLASH_WINDOW_H__

#include "window.h"

class SplashWindow : public Window {
public:
    virtual void beforeRedraw() { }
    virtual void redraw();
    virtual void resize();
    virtual void keyDown (unsigned char key);
};

#endif
