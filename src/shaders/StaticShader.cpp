
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "StaticShader.h"
#include "../util/geometry.h"

StaticShader::StaticShader() : Shader("basic", "basic") {}

void StaticShader::loadTransformationMatrix(const glm::mat4 &matrix) const {
    setUniformMatrix4("u_transformationMatrix", matrix);
}

void StaticShader::loadViewMatrix(Camera camera) const {
    glm::mat4 viewMatrix           = createViewMatrix(camera);
    setUniformMatrix4("u_viewMatrix", viewMatrix);
}

void StaticShader::loadProjectionMatrix(const glm::mat4 &matrix) const {
    setUniformMatrix4("u_projectionMatrix", matrix);
}

void StaticShader::loadLight(Light light) const {
    setUniform3f("u_lightPosition", light.getPos());
    setUniform3f("u_lightColor", light.getColor());
}

void StaticShader::loadSpecular(float shineDamper, float reflectivity) const {
    setUniform1f("u_shineDamper", shineDamper);
    setUniform1f("u_reflectivity", reflectivity);
}

void StaticShader::loadSkyColor(const glm::vec3 &sky) const {
    setUniform3f("u_skyColor", sky);
}
