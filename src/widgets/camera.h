#pragma once

#include "widget.h"
#include <memory>

class EntityManager;
class MapManager;
class ComponentManager;

class Camera : public Widget {
public:
    Camera() = default;
    ~Camera() = default;
    Camera* setManagerRefs(std::shared_ptr<EntityManager> entities,
                           std::shared_ptr<ComponentManager> components,
                           std::shared_ptr<MapManager> map

    ) {
        m_entities = entities;
        m_components = components;
        m_map = map;
        return this;
    }
    Camera* setDebugEnabled(bool enabled) {
        m_debug = enabled;
        return this;
    }

    void render();

private:
    void renderSprites();
    void renderNpcPaths();

private:
    std::shared_ptr<EntityManager> m_entities = nullptr;
    std::shared_ptr<ComponentManager> m_components = nullptr;
    std::shared_ptr<MapManager> m_map = nullptr;

    int m_mapOffsetX = 0;
    int m_mapOffsetY = 0;
    int m_mapOffsetZ = 0;
    unsigned int m_area = 0;
    bool m_debug = false;
};
