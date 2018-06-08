#include "geometry.h"
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr

glm::mat4 createTransformationMatrix(const glm::vec3 &translate, const glm::vec3 &rotate, float scale) {
    // translate an identity matrix to the location
    glm::mat4 viewTranslate = glm::translate(glm::mat4(1.0f), translate);

    // rotate the translated matrix
    glm::mat4 viewRotateX = glm::rotate(viewTranslate, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 viewRotateY = glm::rotate(viewRotateX, rotate.y, glm::vec3(0, 1.0f, 0.0f));
    glm::mat4 viewRotateZ = glm::rotate(viewRotateY, rotate.z, glm::vec3(0, 0.0f, 1.0f));

    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(viewRotateZ, glm::vec3(scale));

    return scaleMatrix;
}

glm::mat4 createProjectionMatrix(int width, int height) {
    return glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.001f, 1000.0f);
}

glm::mat4 createViewMatrix(const glm::vec3 &position) {
    return glm::lookAt(position, glm::vec3(0), glm::vec3(0, 1, 0));
}

glm::mat4 createViewMatrix(const Camera &camera) {

    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateY = glm::rotate(rotateX, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 negativeCamPos = -camera.getPos();
    glm::mat4 translate = glm::translate(rotateY, negativeCamPos);

    return translate;
}