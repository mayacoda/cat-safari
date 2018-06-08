
#ifndef SAFARI_CAMERA_H
#define SAFARI_CAMERA_H


#include <glm/vec3.hpp>

class Camera {
private:
    glm::vec3 m_pos;
    float m_pitch; // x rotation;
    float m_yaw; // y rotation;
    float m_roll; // z rotation;


public:
    Camera();

    const glm::vec3 &getPos() const;

    float getPitch() const;

    float getYaw() const;

    float getRoll() const;

    void move(glm::vec3 position);

    void rotate(glm::vec3 angles);

};


#endif //SAFARI_CAMERA_H
