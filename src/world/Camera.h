
#ifndef SAFARI_CAMERA_H
#define SAFARI_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Player.h"

class Camera {
private:
    glm::vec3 m_pos;
    float     m_pitch; // x rotation;
    float     m_yaw; // y rotation;
    float     m_roll; // z rotation;

    bool m_isPhotoView;


    static const int MIN_ZOOM_DISTANCE = 25;
    static const int MAX_ZOOM_DISTANCE = 10000;

    Player* m_player;
    float m_distanceFromPlayer;
    float m_angleAroundPlayer;


public:
    const static float DEFAULT_PITCH = 20;

    explicit Camera(Player* player);

    const glm::vec3 &getPos() const;

    float getPitch() const;

    void setPitch(float pitch) { m_pitch = pitch; }

    float getYaw() const;

    void setYaw(float yaw) { m_yaw = yaw; }

    float getRoll() const;

    void setRoll(float roll) { m_roll = roll; }

    void togglePhotoView();

    void setAngleAroundPlayer(float angle) { m_angleAroundPlayer = angle; }

    void update() {
        calculatePosition();
    }

    void moveBy(glm::vec3 position);

    void moveTo(glm::vec3 position);


    void rotateBy(glm::vec3 angles);

    void calculateZoom(double zoom);

    void calculatePosition();

    bool isInPhotoView() const { return m_isPhotoView; }

    void rotate(glm::vec3 angles);

};


#endif //SAFARI_CAMERA_H
