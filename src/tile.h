#ifndef __TILE_H__
#define __TILE_H__

typedef enum {
    TILE_PLAIN = 0,
    TILE_WATER = 1,
    TILE_MAX 
    } TILE;

typedef enum {
    CON_EMPTY   = 0,
    CON_WALL    = 1,
    CON_ROAD    = 2,
    CON_MAX
} CONSTRUCTION;

class Tile {
public:
	Tile();
	Tile (TILE type, int x, int y);
	~Tile();

        // Const getters
	int getX () const { return m_x; }
	int getY () const { return m_y; }
        void setX (int x) { m_x = x; }
        void setY (int y) { m_y = y; }
        TILE getBackground() const { return m_background; }
        CONSTRUCTION getConstruction() const { return m_construction; }
        int getElevation() const { return m_elevation; }

        void setBackground (TILE bg) { m_background = bg; }
        void setConstruction (CONSTRUCTION con) { m_construction = con; }
        void setElevation (int elevation) { m_elevation = elevation; }

        int getUnit () { return m_unit; }
        void setUnit (int unit) { m_unit = unit; }

private:
    int	            m_x;
    int	            m_y;
    TILE            m_background;
    CONSTRUCTION    m_construction;
    int             m_elevation;
    int             m_unit;
};

#endif
