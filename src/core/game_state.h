#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

typedef unsigned long long tick_t;
class GameState {
    public:
        bool isPlayerTurn() { return m_playerTurn; }
        void nextTurn() { m_turn++; m_playerTurn = !m_playerTurn; }
        tick_t getTurn() { return m_turn; }

    private:
        bool    m_playerTurn = true;
        tick_t  m_turn = 0;
};

#endif
