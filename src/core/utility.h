#pragma once

#include <functional>

enum class Direction {
    None = 0,
    North = 1,
    East = 2,
    South = 3,
    West = 4,
    NorthEast = 5,
    SouthEast = 6,
    SouthWest = 7,
    NorthWest = 8
};

const int KEY_TAB = 1;
const int KEY_ESC = 2;
const int KEY_ENTER = 3;
const int KEY_UP = 4;
const int KEY_DOWN = 5;
const int KEY_RIGHT = 6;
const int KEY_LEFT = 7;
const int KEY_BACKSPACE = 8;
const int KEY_MAX = 63;

namespace Utility {
unsigned int randBetween(unsigned int start, unsigned int end);
bool randChance(unsigned int percentage);
} // namespace Utility

class Defer {
public:
    explicit Defer(std::function<void()> f) : m_func(f) {}
    ~Defer() { m_func(); }

public:
    std::function<void()> m_func;
};