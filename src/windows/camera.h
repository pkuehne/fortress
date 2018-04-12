#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "widget.h"
class GameState;

class Camera : public Widget
{
  public:
    Camera *setGameState(GameState *state)
    {
        m_state = state;
        return this;
    }
    void setMapOffset(int x, int y, int z);
    void render();
    void renderSprites();
    void renderNpcPaths();
    bool &enabled() { return m_enabled; }

  private:
    GameState *m_state;
    int m_mapOffsetX = 0;
    int m_mapOffsetY = 0;
    int m_mapOffsetZ = 0;
    bool m_enabled = true;
};

#endif
