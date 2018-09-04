#include "geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 Geometry::createTransformationMatrix(const glm::vec3 &translate, const glm::vec3 &rotate, float scale) {
    // translate an identity matrix to the location
    glm::mat4 viewTranslate = glm::translate(glm::mat4(1.0f), translate);

    // rotateBy the translated matrix
    glm::mat4 viewRotateX = glm::rotate(viewTranslate, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 viewRotateY = glm::rotate(viewRotateX, glm::radians(rotate.y), glm::vec3(0, 1.0f, 0.0f));
    glm::mat4 viewRotateZ = glm::rotate(viewRotateY, glm::radians(rotate.z), glm::vec3(0, 0.0f, 1.0f));

    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(viewRotateZ, glm::vec3(scale));

    return scaleMatrix;
}

glm::mat4 Geometry::createProjectionMatrix(int width, int height) {
    return glm::perspective(glm::radians(CAMERA_ANGLE), (float) width / (float) height, NEAR, FAR);
}

glm::mat4 Geometry::createPhotoViewProjectionMatrix(int width, int height) {
    return glm::perspective(glm::radians(PHOTO_ANGLE), (float) width / (float) height, NEAR, FAR);
}

glm::mat4 Geometry::createViewMatrix(const Camera &camera) {

    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateY = glm::rotate(rotateX, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 negativeCamPos = -camera.getPos();
    glm::mat4 translate = glm::translate(rotateY, negativeCamPos);

    return translate;
}