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
    Unit (int id, UNIT type, int x, int y);

    int getId () { return m_id; }
    void setId (int id) { m_id = id; }

    int getX() { return m_x; }
    int getY() { return m_y; }
    void setX (int x) { m_x = x; } 
    void setY (int y) { m_y = y; }

    UNIT getType() { return m_type; }
    
    void setNewDestination (int x, int y);
    int getNextTile (void);
    void moveNextTile (unsigned long long);
    
    bool isDefender () const { return m_defender; }
    bool& isDefender () { return m_defender; }

    bool canSwim () const { return m_canSwim; }
    bool& canSwim () { return m_canSwim; }

    unsigned long long getLastMove () { return m_lastMove; }
    void setLastMove (unsigned long long last) { m_lastMove = last; }

    int getMoveSpeed () { return m_moveSpeed; }
    int getSwimSpeed () { return m_swimSpeed; }

    int& getHitPoints() { return m_hitPoints; }
    int& getTarget() { return m_target; }

    unsigned long long getLastAttack () { return m_lastAttack; }
    void setLastAttack (unsigned long long last) { m_lastAttack = last; }
private:
    void setNewPath (PathVector l_path) { m_path = l_path; }

private:
    int         m_id;
    UNIT        m_type;
    int         m_x;
    int         m_y;
    PathVector  m_path;

    bool        m_defender;
    bool        m_canSwim;

    unsigned long long  m_lastMove;
    int         m_moveSpeed;
    int         m_swimSpeed;
    int         m_hitPoints;
    int         m_target;
    unsigned long long  m_lastAttack;
};

#endif
