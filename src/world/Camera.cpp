
#include "Camera.h"

Camera::Camera(Player* player) : m_pos(glm::vec3(0, 0, 0)),
                                 m_pitch(20),
                                 m_yaw(0),
                                 m_roll(0),
                                 m_distanceFromPlayer(50),
                                 m_angleAroundPlayer(0),
                                 m_player(player) {}


Camera::Camera(Player* player, const glm::vec3 &m_pos, float m_pitch, float m_yaw, float m_roll)
        : m_pos(m_pos),
          m_pitch(m_pitch),
          m_yaw(m_yaw),
          m_roll(m_roll),
          m_distanceFromPlayer(50),
          m_angleAroundPlayer(0),
          m_player(player) {}

const glm::vec3 &Camera::getPos() const {
    return m_pos;
}

float Camera::getPitch() const {
    return m_pitch;
}

float Camera::getYaw() const {
    return m_yaw;
}

float Camera::getRoll() const {
    return m_roll;
}

void Camera::moveBy(glm::vec3 position) {
    m_pos += position;
}

void Camera::rotateBy(glm::vec3 angles) {
    m_pitch += angles.x;
    m_yaw += angles.y;
    m_roll += angles.z;
}

void Camera::rotate(glm::vec3 angles) {
    m_pitch = angles.x;
    m_yaw   = angles.y;
    m_roll  = angles.z;
}

void Camera::moveTo(glm::vec3 position) {
    m_pos = position;
}

void Camera::calculateZoom(double zoom) {
    float distance = m_distanceFromPlayer + (float) zoom;

    // make sure the camera isn't too far away or too close
    if (distance < Camera::MIN_ZOOM_DISTANCE || distance > Camera::MAX_ZOOM_DISTANCE) {
        return;
    }

    m_distanceFromPlayer = distance;
}

void Camera::moveToward(const glm::vec3 &position, float distance) {
    glm::vec3 diff = m_pos - position;
    if (glm::length(diff) < distance) {
        moveTo(position);
    } else {
        moveTo(m_pos - glm::normalize(diff) * distance);
    }
}

void Camera::calculatePosition() {
    float horDist  = m_distanceFromPlayer * glm::cos(glm::radians(m_pitch));
    float vertDist = m_distanceFromPlayer * glm::sin(glm::radians(m_pitch));

    float y     = vertDist + m_player->getPos().y;
    float theta = m_player->getRotation().y + m_angleAroundPlayer;
    m_yaw = 180 - theta;

    float x = m_player->getPos().x - horDist * glm::sin(glm::radians(theta));
    float z = m_player->getPos().z - horDist * glm::cos(glm::radians(theta));

    m_pos = glm::vec3(x, y, z);
}
