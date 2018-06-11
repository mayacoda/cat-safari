
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "TerrainShader.h"
#include "../util/geometry.h"

TerrainShader::TerrainShader() : Shader("terrain", "terrain") {}

void TerrainShader::loadTransformationMatrix(const glm::mat4 &matrix) const {
    setUniformMatrix4("u_transformationMatrix", matrix);
}

void TerrainShader::loadViewMatrix(Camera camera) const {
    glm::mat4 viewMatrix = createViewMatrix(camera);
    setUniformMatrix4("u_viewMatrix", viewMatrix);
}

void TerrainShader::loadProjectionMatrix(const glm::mat4 &matrix) const {
    setUniformMatrix4("u_projectionMatrix", matrix);
}

void TerrainShader::loadLight(Light light) const {
    setUniform3f("u_lightPosition", light.getPos());
    setUniform3f("u_lightColor", light.getColor());
}

void TerrainShader::loadSpecular(float shineDamper, float reflectivity) const {
    setUniform1f("u_shineDamper", shineDamper);
    setUniform1f("u_reflectivity", reflectivity);
}

void TerrainShader::loadSkyColor(const glm::vec3 &sky) const {
    setUniform3f("u_skyColor", sky);
}

void TerrainShader::connectTextureSlots() {
    setUniform1i("u_backgroundTexture", 0);
    setUniform1i("u_rTexture", 1);
    setUniform1i("u_gTexture", 2);
    setUniform1i("u_bTexture", 3);
    setUniform1i("u_blendMap", 4);
}
