#include "camera.h"
#include "../components/npc_component.h"
#include "../components/sprite_component.h"
#include "../core/game_state.h"
#include "../core/graphics.h"
#include "../core/location.h"
#include <glog/logging.h>

void Camera::render() {
    if (!m_state) {
        throw("Game State must be set on Camera");
    }

    Location l_playerLoc = m_state->location(m_state->player());

    m_mapOffsetX = l_playerLoc.x - (getWidth() / 2);
    m_mapOffsetY = l_playerLoc.y - (getHeight() / 2);
    m_mapOffsetZ = l_playerLoc.z;
    m_area = l_playerLoc.area;

    renderSprites();
    if (m_state->debug().showNpcPaths) {
        renderNpcPaths();
    }
}

void Camera::renderSprites() {
    unsigned int tileZ = m_mapOffsetZ;
    for (unsigned int yy = 0; yy < getHeight(); yy++) {
        unsigned int tileY = yy + m_mapOffsetY;
        for (unsigned int xx = 0; xx < getWidth(); xx++) {
            unsigned int tileX = xx + m_mapOffsetX;
            Location loc(tileX, tileY, tileZ, m_area);
            if (!m_state->isValidTile(loc))
                continue;

            Tile& l_tile = m_state->tile(loc);
            std::map<unsigned int, std::vector<const SpriteComponent*>>
                l_sprites;
            for (EntityId entity : l_tile.entities()) {
                SpriteComponent* l_sprite =
                    m_state->components()->get<SpriteComponent>(entity);
                NpcComponent* l_npc =
                    m_state->components()->get<NpcComponent>(entity);
                if (!l_sprite)
                    continue;
                if (l_npc && l_tile.lastVisited() < m_state->turn()) {
                    continue;
                }
                l_sprites[l_sprite->renderLayer].push_back(l_sprite);
            }
            l_sprites[0].push_back(&(l_tile.getSprite()));

            for (auto& layer : l_sprites) {
                for (auto l_sprite : layer.second) {
                    Color fgColor = l_sprite->fgColor;
                    if (l_tile.lastVisited() < m_state->turn()) {
                        fgColor *= 0.4;
                    }

                    if (l_tile.lastVisited() > 0 &&
                        l_tile.lastVisited() + 200 > m_state->turn()) {
                        drawTile(xx, yy, l_sprite->sprite, fgColor,
                                 l_sprite->bgColor);
                    }
                }
            }
        }
    }
    // renderNpcPaths();
}

void Camera::renderNpcPaths() {
    for (EntityId entity : m_state->entities()) {
        Location loc = m_state->location(entity);
        int x = loc.x;
        int y = loc.y;
        if (x < m_mapOffsetX || x + m_mapOffsetX > (int)getWidth() ||
            y < m_mapOffsetY || y + m_mapOffsetY > (int)getHeight()) {
            continue;
        }
        NpcComponent* npc = m_state->components()->get<NpcComponent>(entity);
        if (npc) {
            for (Location stepLoc : npc->path) {
                drawTile(stepLoc.x - m_mapOffsetX, stepLoc.y - m_mapOffsetY,
                         'X', Color(RED), Color(BLACK));
            }
        }
    }
}
