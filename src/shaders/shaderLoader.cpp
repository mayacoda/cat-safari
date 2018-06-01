#include "shaderLoader.h"
#include "../util/fileUtil.h"
#include <GL/glew.h>
#include <iostream>


unsigned int compileShader(unsigned int type, const std::string &source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
    }

    return id;
}

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs      = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs      = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Failed to link program!" << std::endl;
        std::cout << message << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int loadShader(const std::string &vertex, const std::string &fragment) {
    return createShader(getFileContents("./shaders/" + vertex + ".vert"),
                        getFileContents("./shaders/" + fragment + ".frag"));
}