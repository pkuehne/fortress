#ifndef __UNIT_H__
#define __UNIT_H__

#include <vector>

typedef enum {
    UNIT_WARRIOR    = 1,
    UNIT_ARCHER     = 2,
    UNIT_MAX
} UNIT;

typedef std::vector<int> PathVector;

class Unit {
public:
    Unit ();
    Unit (UNIT type, int x, int y);

    int getX() { return m_x; }
    int getY() { return m_y; }
    void setX (int x) { m_x = x; } 
    void setY (int y) { m_y = y; }

    UNIT getType() { return m_type; }
    
    void setNewPath (PathVector l_path) { m_path = l_path; }
    int getNextPath (void);

private:
    UNIT        m_type;
    int         m_x;
    int         m_y;
    PathVector  m_path;
};

#endif
