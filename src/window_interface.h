#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

class GameEngineInterface;

class WindowInterface {
public:
    virtual ~WindowInterface() {}
    virtual void initialise (GameEngineInterface* a_engine) = 0;
    virtual void destroy (void) = 0;

    virtual GameEngineInterface* getEngine() = 0;
    virtual void keyDown (unsigned char key) = 0;
    virtual void keyUp (unsigned char key) = 0;
    virtual bool getKey (unsigned char key) = 0;
    virtual void mouseDown (int x, int y, int button) = 0;
    virtual void mouseUp (int x, int y, int button) = 0;
    virtual void beforeRedraw() = 0;
    virtual void redraw () = 0;
    virtual void afterRedraw() = 0;
    virtual void resize (int width, int height) = 0;
};

#endif
