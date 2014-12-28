#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "tile.h"
#include "unit.h"

class Window 
{
public:
    void initialise (void);
    void destroy (void);
    void keyDown (unsigned char key);
    void keyUp (unsigned char key);
    void mouseDown (int x, int y, int button);
    void mouseUp (int x, int y, int button);
    void redraw ();
    void resize (int width, int height);
    
    void processKeys ();

    void setMapX (int newX);
    void setMapY (int newY);

private:
    void drawTitle ();
    void loadImages ();
    void drawMap ();
    void drawUnits ();

    int screenXToMapX (int screenX);
    int screenYToMapY (int screenY);
    int mapXToScreenX (int mapX);
    int mapYToScreenY (int mapY);

private:
    bool ascii_keys[256];
    bool special_keys[256];
    unsigned char* m_backgrounds[TILE_MAX];
    unsigned char* m_constructions[CON_MAX];
    unsigned char* m_units[UNIT_MAX];
    
    int m_mapWidth;
    int m_mapHeight;
    int m_mapX;
    int m_mapY;

    bool m_showNames;
};

#endif