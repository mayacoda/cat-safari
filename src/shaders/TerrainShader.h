
#ifndef SAFARI_TERRAINSHADER_H
#define SAFARI_TERRAINSHADER_H


#include "Shader.h"
#include "../world/Camera.h"
#include "../world/Light.h"

class TerrainShader : public Shader {
public:
    TerrainShader();

    void loadTransformationMatrix(const glm::mat4 &matrix) const;

    void loadProjectionMatrix(const glm::mat4 &matrix) const;

    void loadViewMatrix(Camera camera) const;

    void loadLight(Light light) const;

    void loadSpecular(float shineDamper, float reflectivity) const;

    void loadSkyColor(const glm::vec3 &sky) const;
};


#endif //SAFARI_TERRAINSHADER_H
