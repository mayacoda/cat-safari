#ifndef SAFARI_MOUSE_PICKING_H
#define SAFARI_MOUSE_PICKING_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

namespace MousePicking {
    namespace {
        glm::vec2 toOpenGLCoords(double x, double y, int width, int height) {
            return glm::vec2((2.0f * x) / (double) width - 1.0f, -((2.0f * y) / (double) height - 1.0f));
        }

        glm::vec4 toEyeCoords(const glm::vec4 &clipCoords, const glm::mat4 &projMat) {
            glm::mat4 inverted = glm::inverse(projMat);
            glm::vec4 eyeCords = inverted * clipCoords;
            return glm::vec4(eyeCords.x, eyeCords.y, -1.0f, 0.0f);
        }

        glm::vec3 toWorldCoords(const glm::vec4 &eyeCoords, const glm::mat4 &viewMat) {
            glm::mat4 inverted = glm::inverse(viewMat);
            glm::vec4 ray      = inverted * eyeCoords;
            glm::vec3 mouseRay = glm::vec3(ray.x, ray.y, ray.z);
            return glm::normalize(mouseRay);
        }
    }

    glm::vec3 screenToWorldPos(double x,
                               double y,
                               int width,
                               int height,
                               const glm::mat4 &projMat,
                               const glm::mat4 &viewMat) {

        glm::vec2 openGLCoords = toOpenGLCoords(x, y, width, height);
        // make ray pointing into screen
        glm::vec4 clipCoords   = glm::vec4(openGLCoords.x, openGLCoords.y, -1.0f, 1.0f);
        glm::vec4 eyeCoords    = toEyeCoords(clipCoords, projMat);
        return toWorldCoords(eyeCoords, viewMat);
    }

    glm::vec2 worldToScreenPos(const glm::vec3 &worldPos,
                               int width,
                               int height,
                               const glm::mat4 &modelMat,
                               const glm::mat4 &viewMat,
                               const glm::mat4 &projMat) {
        // where the model is bound within the world
        glm::vec4 posInWorld = modelMat * glm::vec4(worldPos.x, worldPos.y, worldPos.z, 1);

        glm::vec4 posRelativeToCam = viewMat * posInWorld;

        // world space to eye space to projection plane
        glm::vec4 position = projMat * posRelativeToCam;

        // perspective divide
        float pX = position.x / -position.z;
        float pY = position.y / -position.z;

        // convert to pixels on screen
        auto x = static_cast<float>(((pX + 1) / 2.0) * width);
        auto y = static_cast<float>(((pY + 1) / 2.0) * height);

        return glm::vec2(x, y);
    }
}


#endif //SAFARI_MOUSE_PICKING_H
