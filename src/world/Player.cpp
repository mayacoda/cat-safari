
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
