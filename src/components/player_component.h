#pragma once

#include "../core/entity.h"

struct PlayerComponent {
    unsigned long turn = 0;
    bool playerTurn = false;
};
