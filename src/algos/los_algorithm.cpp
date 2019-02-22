#include "los_algorithm.h"
#include "../components/collider_component.h"
#include "../core/component_manager.h"
#include "../core/location.h"
#include "../core/map_manager.h"

bool LosAlgorithm::hasLos(const Location& start, const Location& end) {
    if (start.z != end.z)
        return false;

    int delta_x(end.x - start.x);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(end.y - start.y);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    // check (x1, y1);
    Location step = start;

    if (delta_x >= delta_y) {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (step.x != end.x) {
            if ((error >= 0) && (error || (ix > 0))) {
                error -= delta_x;
                step.y += iy;
            }
            // else do nothing

            error += delta_y;
            step.x += ix;

            if (viewBlocked(step) && step.x != end.x)
                return false;
        }
    } else {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (step.y != end.y) {
            if ((error >= 0) && (error || (iy > 0))) {
                error -= delta_y;
                step.x += ix;
            }
            // else do nothing

            error += delta_x;
            step.y += iy;

            if (viewBlocked(step) && step.y != end.y)
                return false;
        }
    }
    return true;
}

bool LosAlgorithm::viewBlocked(const Location& loc) {
    EntityHolder entities = m_map->findEntitiesAt(loc);
    for (EntityId entity : entities) {
        if (m_components->get<ColliderComponent>(entity)) {
            return true;
        }
    }
    return false;
}
