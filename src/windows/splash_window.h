#ifndef __SPLASH_WINDOW_H__
#define __SPLASH_WINDOW_H__

#include "window.h"

class SplashWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();
    virtual void keyPress (unsigned char key);
};

#endif
