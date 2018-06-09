
#include "Light.h"

Light::Light(const glm::vec3 &m_pos, const glm::vec3 &m_color) : m_pos(m_pos), m_color(m_color) {}

const glm::vec3 &Light::getPos() const {
    return m_pos;
}

const glm::vec3 &Light::getColor() const {
    return m_color;
}
