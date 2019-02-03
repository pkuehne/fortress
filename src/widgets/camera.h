#pragma once

#include "widget.h"
#include <memory>

class GameState;
class EntityManager;

class Camera : public Widget {
public:
    Camera() = default;
    ~Camera() = default;
    Camera* setGameState(GameState* state);

    void render();
    void renderSprites();
    void renderNpcPaths();

private:
    GameState* m_state = 0;
    std::shared_ptr<EntityManager> m_entities = nullptr;

    int m_mapOffsetX = 0;
    int m_mapOffsetY = 0;
    int m_mapOffsetZ = 0;
    unsigned int m_area = 0;
};
