#ifndef FOV_ALGORITHM
#define FOV_ALGORITHM

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

class FovAlgorithm {
public:
    FovAlgorithm() {}
    ~FovAlgorithm() {}
    void initialise(GameEngine* engine) { m_engine = engine; }
    void calculateFov();

private:
    void transformOctant(unsigned int row, unsigned int col,
                         unsigned int octant, int& outY, int& outX);
    Shadow projectTile(double row, double col);

private:
    GameEngine* m_engine = nullptr;
};

#endif
