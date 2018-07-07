#include "Entity.h"

Entity::Entity(TexturedModel* m_model, const glm::vec3 &m_pos, const glm::vec3 &m_rot, float m_scale) : m_model(m_model),
                                                                                                        m_pos(m_pos),
                                                                                                        m_rot(m_rot),
                                                                                                        m_scale(m_scale) {
    m_id = generateId();
}

Entity::Entity(TexturedModel* model) : m_model(model),
                                       m_pos(glm::vec3(0, 0, 0)),
                                       m_rot(glm::vec3(0, 0, 0)),
                                       m_scale(1.0f) {
    m_id = generateId();
}

void Entity::increasePosition(float dx, float dy, float dz) {
    m_pos += glm::vec3(dx, dy, dz);
}

void Entity::increaseRotation(float dx, float dy, float dz) {
    m_rot += glm::vec3(dx, dy, dz);
}
