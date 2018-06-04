
#include <GL/glew.h>
#include "Shader.h"
#include "shaderLoader.h"
#include "../util/GL.h"

Shader::Shader(const std::string &vertex, const std::string &fragment) {
    m_shaderId = loadShader(vertex, fragment);
}

Shader::~Shader() {
    debug(glDeleteProgram(m_shaderId));
}

int Shader::getUniformLocation(const std::string &name) {
    if (m_uniformCache.find(name) != m_uniformCache.end()) {
        return m_uniformCache[name];
    }

    GLint location = glGetUniformLocation(m_shaderId, name.c_str());
    if (location == -1) {
        std::cout << "[Shader::getUniformLocation] could not find uniform" << std::endl;
    }

    m_uniformCache[name] = location;

    return location;
}

void Shader::bind() const {
    debug(glUseProgram(m_shaderId));
}

void Shader::unbind() const {
    debug(glUseProgram(0));
}


void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    int location = getUniformLocation(name);
    debug(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string &name, int v) {
    int location = getUniformLocation(name);
    debug(glUniform1i(location, v));
}
