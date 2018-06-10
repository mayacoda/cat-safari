
#include "Camera.h"

Camera::Camera() : m_pos(glm::vec3(0, 0, 1)),
                   m_pitch(0),
                   m_yaw(0),
                   m_roll(0) {}


Camera::Camera(const glm::vec3 &m_pos, float m_pitch, float m_yaw, float m_roll) : m_pos(m_pos),
                                                                                   m_pitch(m_pitch),
                                                                                   m_yaw(m_yaw),
                                                                                   m_roll(m_roll) {}


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

void Camera::move(glm::vec3 position) {
    m_pos = position;
}

void Camera::rotate(glm::vec3 angles) {
    m_pitch += angles.x;
    m_yaw += angles.y;
    m_roll += angles.z;
}
