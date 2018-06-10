
#ifndef SAFARI_BASICSHADER_H
#define SAFARI_BASICSHADER_H


#include "Shader.h"
#include "../world/Camera.h"
#include "../world/Light.h"

class StaticShader: public Shader {
public:
    StaticShader(const std::string &vertex, const std::string &fragment);

    void loadTransformationMatrix(const glm::mat4 &matrix) const;

    void loadProjectionMatrix(const glm::mat4 &matrix) const;

    void loadViewMatrix(Camera camera) const;

    void loadLight(Light light) const;

    void loadSpecular(float shineDamper, float reflectivity) const;
};


#endif //SAFARI_BASICSHADER_H
