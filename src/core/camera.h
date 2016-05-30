#ifndef __CAMERA_H__
#define __CAMERA_H__

class GameState;
class Graphics;

struct Viewport {
    unsigned int    x;
    unsigned int    y;
    unsigned int    width;
    unsigned int    height;
};

class Camera 
{
public:
    Camera (Graphics* graphics, GameState* state);
    void setMapOffset (unsigned int x, unsigned y, unsigned z);
    void render(); 
    bool& enabled() { return m_enabled; }
    Viewport& viewport () { return m_viewport; }
private:
    Graphics*       m_graphics;
    GameState*      m_state;
    Viewport        m_viewport = {0};
    unsigned int    m_mapOffsetX = 0;
    unsigned int    m_mapOffsetY = 0;
    unsigned int    m_mapOffsetZ = 0;
    bool            m_enabled;
};

#endif
