
#ifndef SAFARI_CAMERA_H
#define SAFARI_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.hpp>

class Camera {
private:
    glm::vec3 m_pos;
    float m_pitch; // x rotation;
    float m_yaw; // y rotation;
    float m_roll; // z rotation;


public:
    Camera();

    Camera(const glm::vec3 &m_pos, float m_pitch, float m_yaw, float m_roll);

    const glm::vec3 &getPos() const;

    float getPitch() const;

    float getYaw() const;

    float getRoll() const;

    void moveBy(glm::vec3 position);

    void moveTo(glm::vec3 position);

    void moveToward(const glm::vec3 &position, float distance) {
        glm::vec3 diff = m_pos - position;
        if (glm::length(diff) < distance) {
            moveTo(position);
        } else {
            moveTo(m_pos - glm::normalize(diff) * distance);
        }
    }

    void rotateBy(glm::vec3 angles);

    void rotate(glm::vec3 angles);

};


#endif //SAFARI_CAMERA_H
