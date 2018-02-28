#ifndef ESCAPE_WINDOW_H
#define ESCAPE_WINDOW_H

#include "window.h"

class EscapeWindow : public Window
{
  public:
    void registerWidgets();

    void keyDown(unsigned char key);
};

#endif
