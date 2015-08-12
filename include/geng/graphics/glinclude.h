#ifndef GLINCLUDE_H
#define GLINCLUDE_H

#include "types/Exception.h"
#ifdef WEB
#else
    #include <GL/glew.h>
#endif
#include <iostream>
#include <string>

#ifndef NDEBUG
inline void printGLError(const char* function, const char* file, int line) {
    GLenum err_code;
    if ((err_code=glGetError())!=GL_NO_ERROR) { \
        printf("(%s:%d) %s: [%d] %s:\n", file, line, function, err_code, (const char*)gluErrorString(err_code)); \
    }
}
#define GLCall(x) \
    x; printGLError(#x, __FILE__, __LINE__);
#else
	#define GLCall(x) x
#endif

namespace grynca {

    struct GL_Exception : public Exception
    {
        GL_Exception() throw()
                : Exception(std::string("OpenGL : ") + (const char*)gluErrorString(glGetError())) {}

        GL_Exception(const char * text) throw()
                : Exception(std::string("OpenGL : ") + text + " - " + (const char*)gluErrorString(glGetError())) {}
    };

    struct GLEW_Exception : public Exception
    {
        GLEW_Exception(unsigned int error) throw()
                : Exception(std::string("GLEW : ") + (char*)glewGetErrorString(error)) {}

        GLEW_Exception(const char * text, unsigned int error) throw()
                : Exception(std::string("GLEW : ") + text + " - " + (char*)glewGetErrorString(error)) {}
    };

}

#endif //GLINCLUDE_H
