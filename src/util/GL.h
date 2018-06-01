
#ifndef SAFARI_GL_H
#define SAFARI_GL_H

#include <GL/glew.h>
#include <iostream>
#include "config.h"

#ifdef DEBUG
#define ASSERT(x) if (!(x)) throw;
#define debug(x) GL::clearError();\
    x;\
    ASSERT(GL::logCall(#x, __FILE__, __LINE__))
#else
#define debug(x) x
#endif

class GL {

private:
    static std::string mapErrorToMessage(unsigned int error);
public:
    static void clearError();

    static bool logCall(const char* function, const char* file, int line);

    static size_t typeToSizeOf(unsigned int type);
};


#endif //SAFARI_GL_H
