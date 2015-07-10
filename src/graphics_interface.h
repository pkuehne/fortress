#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H

class GraphicsInterface {
public:
    virtual ~GraphicsInterface() {}
    virtual initialise() = 0;
    virtual beginScreenUpdate() = 0;
    virtual endScreenUpdate() = 0;
private:

};

#endif
