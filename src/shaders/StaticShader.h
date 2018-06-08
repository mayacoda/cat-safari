
#ifndef SAFARI_BASICSHADER_H
#define SAFARI_BASICSHADER_H


#include "Shader.h"

class StaticShader: public Shader {
public:
    StaticShader(const std::string &vertex, const std::string &fragment);

    void loadTransformationMatrix(glm::mat4 matrix);
};


#endif //SAFARI_BASICSHADER_H
