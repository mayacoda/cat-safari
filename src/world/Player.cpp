
#include "Player.h"

void Player::update(float dt) {

    increaseRotation(0, m_currentTurnSpeed * dt, 0);
    float distance = m_currentSpeed * dt;

    glm::vec3 velocity(0, 0, distance);
    velocity = glm::rotateY(velocity, glm::radians(getRotation().y));
    increasePosition(velocity.x, 0, velocity.z);

    m_upwardSpeed += GRAVITY * dt;

    increasePosition(0, m_upwardSpeed, 0);

    if (getPos().y < 0) {
        m_upwardSpeed = 0;
        setY(0);
    }


}

void Player::moveRight() {
    //@todo implement strafing
    m_pos.x += -cos(m_rot.y);
    m_pos.z += -sin(m_rot.y);
}

void Player::moveLeft() {
    //@todo implement strafing
    m_pos.x += cos(m_rot.y);
    m_pos.z += sin(m_rot.y);
}
