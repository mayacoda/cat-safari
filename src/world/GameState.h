
#ifndef SAFARI_GAMESTATE_H
#define SAFARI_GAMESTATE_H


class GameState {
private:
    int m_state;

public:
    enum STATE {
        menu,
        play,
        win,
        exit
    };

    GameState() : m_state(menu) {}

    STATE getState() const { return static_cast<STATE>(m_state); }

    void setState(STATE state) { m_state = state; }
};


#endif //SAFARI_GAMESTATE_H
