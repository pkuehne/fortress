#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "window.h"
#include <vector>

class Screen {
public:
    Screen ();
    ~Screen();
    void start (void);

    void keyDown (unsigned char key);
    void keyUp (unsigned char key);
    void redraw ();
    void resize (int width, int height);
    void initialise ();

    int getHeight () { return m_screenHeight; }
    int getWidth ()  { return m_screenWidth; }

private:
    Window              m_mapWindow;
    std::vector<Window> m_windows;
    int                 m_screenHeight;
    int                 m_screenWidth;
};

#endif
