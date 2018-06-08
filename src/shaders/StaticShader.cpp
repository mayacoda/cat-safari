
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "StaticShader.h"

StaticShader::StaticShader(const std::string &vertex, const std::string &fragment) : Shader("basic", "basic") {}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    int location = getUniformLocation("u_transformationMatrix");

}
