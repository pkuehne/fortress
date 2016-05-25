#include "game_state.h"
#include "map_manager.h"
#include <stdexcept>
#include <glog/logging.h>

GameState::GameState (MapManager* map)
: m_map (map)
{
    if (m_map == nullptr) {
        LOG(ERROR) << "Game State initialised with nullptr" << std::endl;
        throw std::logic_error ("Input parameter cannot be nullptr");
    }

}

Tile& GameState::tile (const Location& location)
{
    return m_map->getTile (location);
}

MapManager* GameState::map()
{
    return m_map;
}
