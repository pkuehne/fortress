#pragma once

#include "widget.h"
class GameState;

class Camera : public Widget {
public:
    Camera() = default;
    ~Camera() = default;
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
    unsigned int m_area = 0;
};
