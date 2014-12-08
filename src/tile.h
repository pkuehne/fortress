#ifndef __TILE_H__
#define __TILE_H__

typedef enum {
    TILE_PLAIN = 1,
    TILE_WATER = 2,
    TILE_HILL  = 3,
    TILE_MARSH = 4,
    TILE_FORD  = 5,
    TILE_ROAD  = 6,
    TILE_MOUNT = 7,
    TILE_VOID  = 99
    } TILE;


class Tile {
public:
	Tile();
	Tile (char symbol, int x, int y);
	~Tile();

        // Const getters
	char getSymbol () const;
	int getX () const { return m_x; }
	int getY () const { return m_y; }
        int getType() const { return m_type; }
        int getElevation() const { return m_elevation; }
        int getCost () const;
        bool isBlocked () const { return m_blocked; }

        void setType (int type) { m_type = type; }
        void setElevation (int elevation) { m_elevation = elevation; }
private:
    char    m_symbol;
    int	    m_x;
    int	    m_y;
    int     m_type;
    int     m_elevation;
    bool    m_blocked;
};

#endif
