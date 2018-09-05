
#ifndef SAFARI_ENTITY_H
#define SAFARI_ENTITY_H


#include <glm/vec3.hpp>
#include "../models/TexturedModel.h"

class Entity {
private:
    int m_id;

    int generateId() {
        static int id = 0;
        return id++;
    }

protected:
    TexturedModel* m_model;

    // position
    glm::vec3 m_pos;

    // rotation
    glm::vec3 m_rot;

    // scale
    float m_scale;

public:
    Entity(TexturedModel* m_model,
           const glm::vec3 &m_pos,
           const glm::vec3 &m_rot,
           float m_scale);

    virtual ~Entity() {}

    void increasePosition(float dx, float dy, float dz);

    void increaseRotation(float dx, float dy, float dz);

    const TexturedModel* getModel() const { return m_model; }

    const glm::vec3 &getPos() const { return m_pos; }

    const glm::vec3 &getRotation() const { return m_rot; }

    const int getId() const { return m_id; }

    const float getScale() const { return m_scale; }

    void setX(float x) { m_pos.x = x; }

    void setY(float y) { m_pos.y = y; }

    void setZ(float z) { m_pos.z = z; }
};


#endif //SAFARI_ENTITY_H
