#ifndef __CAMERA_H__
#define __CAMERA_H__

class GameState;
class GraphicsInterface;

struct Viewport {
public:
    unsigned int    x;
    unsigned int    y;
    unsigned int    width;
    unsigned int    height;
};

class Camera 
{
public:
    Camera (GraphicsInterface* graphics, GameState* state);
    void setMapOffset (int x, int y, int z);
    void render(); 
    bool& enabled() { return m_enabled; }
    Viewport& viewport () { return m_viewport; }
private:
    GraphicsInterface* m_graphics;
    GameState*  m_state;
    Viewport    m_viewport = {0};
    int         m_mapOffsetX = 0;
    int         m_mapOffsetY = 0;
    int         m_mapOffsetZ = 0;
    bool        m_enabled = true;
};

#endif
