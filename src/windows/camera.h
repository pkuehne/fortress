#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "widget.h"
class GameState;

class Camera : public Widget {
public:
    Camera() {}
    ~Camera() {}
    Camera* setGameState(GameState* state) {
        m_state = state;
        return this;
    }
    void render();
    void renderSprites();
    void renderNpcPaths();

private:
    GameState* m_state = 0;
    int m_mapOffsetX = 0;
    int m_mapOffsetY = 0;
    int m_mapOffsetZ = 0;
};

#endif
