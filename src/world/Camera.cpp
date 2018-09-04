
#include "Camera.h"
#include "../util/geometry.h"

Camera::Camera(Player* player, float ratio) : m_pos(glm::vec3(0, 0, 0)),
                                              m_pitch(20),
                                              m_yaw(0),
                                              m_roll(0),
                                              m_isPhotoView(false),
                                              m_angleAroundPlayer(0),
                                              m_distanceFromPlayer(50),
                                              m_player(player) {
    m_frustum = new Frustum();
    m_frustum->setCameraInternals(m_isPhotoView ? Geometry::PHOTO_ANGLE : Geometry::CAMERA_ANGLE,
                                  ratio,
                                  Geometry::NEAR,
                                  Geometry::FAR);
}


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

void Camera::calculatePosition() {
    float horDist, vertDist;

    if (!m_isPhotoView) {
        horDist  = m_distanceFromPlayer * glm::cos(glm::radians(m_pitch));
        vertDist = m_distanceFromPlayer * glm::sin(glm::radians(m_pitch));
    } else {
        horDist = -1.5f;
        vertDist = 8.5;
    }

    float y     = vertDist + m_player->getPos().y;
    float theta = m_player->getRotation().y + m_angleAroundPlayer;
    m_yaw = 180 - theta;

    float x = m_player->getPos().x - horDist * glm::sin(glm::radians(theta));
    float z = m_player->getPos().z - horDist * glm::cos(glm::radians(theta));

    m_pos = glm::vec3(x, y, z);

    float xzLength = glm::cos(glm::radians(m_pitch));
    float dirX = xzLength * glm::sin(glm::radians(m_yaw));
    float dirY = glm::sin(glm::radians(-m_pitch));
    float dirZ = -xzLength * glm::cos(glm::radians(-m_yaw));
    glm::vec3 dirCalc = glm::normalize(glm::vec3(dirX, dirY, dirZ));

    glm::vec3 lookAt = m_pos + dirCalc;

    m_frustum->setCameraDef(m_pos, lookAt, glm::vec3(0, 1, 0));
}

void Camera::togglePhotoView(int width, int height) {
    m_isPhotoView = !m_isPhotoView;

    m_frustum->setCameraInternals(m_isPhotoView ? Geometry::PHOTO_ANGLE : Geometry::CAMERA_ANGLE,
                                  (float) width / (float) height,
                                  Geometry::NEAR,
                                  Geometry::FAR);
}

bool Camera::isInView(Entity* entity) const {
    std::vector<glm::vec3> points = entity->getModel()->getBoundingBox().points;


    for (auto it = points.begin(); it != points.end(); ++it) {
        glm::mat4 modelMatrix = Geometry::createTransformationMatrix(entity->getPos(),
                                                                     entity->getRotation(),
                                                                     entity->getScale());

        glm::vec4 worldPos = modelMatrix * glm::vec4((*it), 1);

        Frustum::POINT_STATE state = m_frustum->pointInFrustum(glm::vec3(worldPos));
        if (state != Frustum::OUTSIDE) {
            return true;
        }
    }

    return false;

}

Camera::~Camera() {
    delete m_frustum;
}
