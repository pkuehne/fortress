#include "entity.h"


bool operator< (const Entity& lhs, const Entity& rhs) {
    return lhs.getId() < rhs.getId();
}
