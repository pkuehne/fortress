#include "camera.h"
#include "location.h"
#include "game_state.h"
#include "graphics.h"
#include "sprite_component.h"
#include "npc_component.h"

Camera::Camera (GraphicsInterface* graphics, GameState* state)
: m_graphics (graphics)
, m_state (state)
{

}

void Camera::setMapOffset (int x, int y, int z)
{
    m_mapOffsetX = x;
    m_mapOffsetY = y;
    m_mapOffsetZ = z;
}

void Camera::render()
{
    unsigned int tileZ = m_mapOffsetZ;
    for (unsigned int yy = 0; yy < m_viewport.height; yy++) {
        unsigned int tileY = yy + m_mapOffsetY;
        for (unsigned int xx = 0; xx < m_viewport.width; xx++) {
            unsigned int tileX = xx + m_mapOffsetX;
            Location loc (tileX, tileY, tileZ);
            if (!m_state->isValidTile (loc)) continue;

            Tile& l_tile = m_state->tile(loc);
            std::map<unsigned int, std::vector<SpriteComponent*> > l_sprites;
            for (EntityId entity : l_tile.entities()) {
                SpriteComponent* l_sprite = m_state->components()->get<SpriteComponent> (entity);
                if (!l_sprite) continue;
                l_sprites[l_sprite->renderLayer].push_back (l_sprite);
            }
            l_sprites[0].push_back (&(l_tile.getFloor().getSprite()));

            for (auto& layer : l_sprites) {
                for (SpriteComponent* l_sprite : layer.second) {
                    Color fgColor = l_sprite->fgColor;
                    if (l_tile.lastVisited < m_state->turn()) {
                        fgColor *= 0.4;
                    }

                    if (l_tile.lastVisited > 0 && l_tile.lastVisited + 200 > m_state->turn()) {
                        m_graphics->drawTile (  m_viewport.y + yy,
                                                m_viewport.x + xx,
                                                l_sprite->sprite,
                                                fgColor,
                                                l_sprite->bgColor);
                    }
                }
            }
        }
    }
    //renderNpcPaths();
}
void Camera::renderNpcPaths()
{
    for (EntityId entity : m_state->entities()) {
        Location loc = m_state->location(entity);
        int x = loc.x;
        int y = loc.y;
        if (    x < m_mapOffsetX || x + m_mapOffsetX > (int) m_viewport.width || 
                y < m_mapOffsetY || y + m_mapOffsetY > (int) m_viewport.height) {
            continue;
        }
        NpcComponent* npc = m_state->components()->get<NpcComponent> (entity);
        if (npc) {
            for (Location stepLoc : npc->path) {
                m_graphics->drawTile (  stepLoc.y - m_mapOffsetY + m_viewport.y,
                                        stepLoc.x - m_mapOffsetX + m_viewport.x,
                                        'X',
                                        Color (RED),
                                        Color (BLACK));
            }
        }
    }
}
