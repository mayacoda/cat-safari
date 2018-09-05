
#ifndef SAFARI_PLAYER_H
#define SAFARI_PLAYER_H


#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Entity.h"

class Player : public Entity {
private:

    float m_currentSpeed;
    float m_currentTurnSpeed;
    float m_upwardSpeed;

public:
    static const int   MAX_SPEED      = 30;
    static const int   MAX_TURN_SPEED = 120;
    static const int   GRAVITY        = -8;
    static const int   JUMP_POWER     = 2;

    Player(TexturedModel* m_model, const glm::vec3 &m_pos, const glm::vec3 &m_rot, float m_scale) : Entity(m_model,
                                                                                                           m_pos,
                                                                                                           m_rot,
                                                                                                           m_scale),
                                                                                                    m_currentSpeed(0),
                                                                                                    m_currentTurnSpeed(0),
                                                                                                    m_upwardSpeed(0) {}

    void update(float dt, const std::vector<Entity*> &obstacles);

    void jump() { if (getPos().y == 0) { m_upwardSpeed = JUMP_POWER; }}

    void setSpeed(int speed) { m_currentSpeed = speed; }

    void setTurnSpeed(int speed) { m_currentTurnSpeed = speed; }
};


#endif //SAFARI_PLAYER_H
