#ifndef __SPLASH_WINDOW_H__
#define __SPLASH_WINDOW_H__

#include "window.h"

class SplashWindow : public Window {
public:
    virtual void beforeRedraw() { }
    virtual void redraw();
};

#endif
