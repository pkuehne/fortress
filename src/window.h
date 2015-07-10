#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "window_interface.h"
class GameEngineInterface;

class Window : public WindowInterface
{
public:
    Window(): m_engine(0) { }
    virtual ~Window() { }
    virtual void initialise (GameEngineInterface* a_engine);
    virtual void destroy (void);

    virtual GameEngineInterface* getEngine() { return m_engine; }
    virtual void keyDown (unsigned char key) { ascii_keys[key] = true; }
    virtual void keyUp (unsigned char key) { ascii_keys[key] = false; }
    virtual bool getKey (unsigned char key) { return ascii_keys[key]; }
    virtual void mouseDown (int x, int y, int button);
    virtual void mouseUp (int x, int y, int button);
    virtual void beforeRedraw();
    virtual void redraw () { };
    virtual void afterRedraw();
    virtual void resize (int width, int height);

private:
    bool                ascii_keys[256];
    bool                special_keys[256];
    GameEngineInterface*    m_engine;
};

#endif
