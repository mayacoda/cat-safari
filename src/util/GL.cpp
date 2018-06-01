
#include "GL.h"

bool GL::logCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: " << GL::mapErrorToMessage(error) << std::endl;
        std::cout << "on " << function << " in " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void GL::clearError() {
    while (glGetError() != GL_NO_ERROR);
}

std::string GL::mapErrorToMessage(unsigned int error) {
    switch (error) {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM\nAn unacceptable value is specified for an enumerated argument.";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE\nA numeric argument is out of range.";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION\nThe specified operation is not allowed in the current state.";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW\nThis command would cause a stack overflow.";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW\nThis command would cause a stack underflow.";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY\nThere is not enough memory left to execute the command.";
        case GL_TABLE_TOO_LARGE:
            return "GL_TABLE_TOO_LARGE\nThe specified table exceeds the implementation's maximum supported table size.";
        default:
            return "UNKNOWN ERROR";
    }
}

size_t GL::typeToSizeOf(unsigned int type) {
    switch (type) {
        case GL_INT:
            return sizeof(GLint);
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        default:
            std::cout << "GL TYPE CURRENTLY UNSUPORTED: " << type << std::endl;
            return 0;
    }
}
