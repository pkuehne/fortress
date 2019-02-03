#pragma once

#include "../core/game_engine.h"

class Shadow {
public:
    Shadow(double s, double e) : start(s), end(e) {}
    bool contains(const Shadow& other) const;

public:
    double start;
    double end;
};

class ShadowLine {
public:
    bool isInShadow(const Shadow& projection);
    bool isInFullShadow();
    void addShadow(Shadow shadow);

private:
    std::vector<Shadow> m_shadows;
};

class EntityManager;

class FovAlgorithm {
public:
    FovAlgorithm() {}
    ~FovAlgorithm() {}
    void initialise(GameEngine* engine,
                    std::shared_ptr<EntityManager> entities) {
        m_engine = engine;
        m_entities = entities;
    }
    void calculateFov();

private:
    void transformOctant(unsigned int row, unsigned int col,
                         unsigned int octant, int& outY, int& outX);
    Shadow projectTile(double row, double col);

private:
    GameEngine* m_engine = nullptr;
    std::shared_ptr<EntityManager> m_entities = nullptr;
};
