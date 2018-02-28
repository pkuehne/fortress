#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "main_window.h"
#include "window.h"

class MainWindow : public Window {
public:
    virtual void registerWidgets();
    virtual void keyDown (unsigned char key);

private:

};

#endif
