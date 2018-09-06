
#include "Player.h"
#include "../util/geometry.h"
#include "../util/Collisions.h"
#include <glm/gtx/vector_angle.hpp>

void Player::update(float dt, const std::vector<Entity*> &obstacles) {

    increaseRotation(0, m_currentTurnSpeed * dt, 0);
    float distance = m_currentSpeed * dt;

    glm::vec3 velocity(0, 0, distance);
    velocity = glm::rotateY(velocity, glm::radians(getRotation().y));
    glm::vec3 nextPos = m_pos + glm::vec3(velocity.x, 0, velocity.z);

    if (nextPos != m_pos) {
        // scaling down the bounding box so it looks better
        glm::mat4 modelMat = Geometry::createTransformationMatrix(m_pos, m_rot, m_scale);

        bool hasCollision = false;
        // test collisions
        for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
            Entity* e = *it;
            if (e->getId() == getId()) continue;
            glm::mat4 obsModelMat = Geometry::createTransformationMatrix(e->getPos(), e->getRotation(), e->getScale());

            if (Collisions::isHit(m_model->getBoundingBox(), modelMat, e->getModel()->getBoundingBox(), obsModelMat)) {
                hasCollision = true;
                break;
            }
        }

        if (!hasCollision) {
            m_pos = nextPos;
        }
    }

    m_upwardSpeed += GRAVITY * dt;

    increasePosition(0, m_upwardSpeed, 0);

    if (getPos().y < 0) {
        m_upwardSpeed = 0;
        setY(0);
    }


}