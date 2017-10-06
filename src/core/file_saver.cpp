#include "file_saver.h"
#include "game_engine.h"
#include <typeinfo>
#include "collider_component.h"
#include "consumable_component.h"
#include "description_component.h"
#include "droppable_component.h"
#include "equipment_component.h"
#include "health_component.h"
#include "npc_component.h"
#include "player_component.h"
#include "sprite_component.h"
#include "stair_component.h"
#include "wearable_component.h"
#include "wieldable_component.h"
#include <glog/logging.h>

void FileSaver::saveState ()
{

    // Save Map
    MapManager* map = m_engine->state()->map();
    unsigned int height = map->getMapHeight();
    unsigned int width = map->getMapWidth();
    unsigned int depth = map->getMapDepth();

    for (unsigned int d = 0; d < depth; d++) {
        for (unsigned int h = 0; h < height; h++) {
            for (unsigned int w = 0; w < width; w++) {
                Location loc (w, h, d, 0);
                const Tile& tile = map->getTile(loc);
                std::cout << "Tile: " << tile.lastVisited << std::endl;
            }
        }
    }

}

