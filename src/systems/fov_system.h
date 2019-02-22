#pragma once

#include "../core/game_system_base.h"

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

class FovSystem : public GameSystemBase {
public:
    void registerHandlers();

private:
    void calculateFov();
    void transformOctant(unsigned int row, unsigned int col,
                         unsigned int octant, int& outY, int& outX);
    Shadow projectTile(double row, double col);
};