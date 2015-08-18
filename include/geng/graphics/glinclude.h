#ifndef GLINCLUDE_H
#define GLINCLUDE_H

#include "types/Exception.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

namespace grynca {

    static std::string GLErrorString() {
        GLenum err = glGetError();
        std::string err_s = "[" +std::to_string(err)+ "]";
#ifndef WEB
        // emscripten does not have gluErrorString()
        err_s += std::string(": ")+(const char*)gluErrorString(err);
#endif
        return err_s;
    }

    static void printGLError(const char* function, const char* file, int line) {
        GLenum err_code;
        if ((err_code=glGetError())!=GL_NO_ERROR) {
            std::cerr << "(" << file << ":" << line << ") " << function << ": " << grynca::GLErrorString() << std::endl;
        }
    }

    struct GL_Exception : public Exception
    {
        GL_Exception() throw()
                : Exception(std::string("OpenGL : ") + GLErrorString()) {}

        GL_Exception(const char * text) throw()
                : Exception(std::string("OpenGL : ") + text + " - " + GLErrorString()) {}
    };

    struct GLEW_Exception : public Exception
    {
        GLEW_Exception(unsigned int error) throw()
                : Exception(std::string("GLEW : ") + GLErrorString()) {}

        GLEW_Exception(const char * text, unsigned int error) throw()
                : Exception(std::string("GLEW : ") + text + " - " + GLErrorString()) {}
    };

}

#ifndef NDEBUG
#define GLCall(x) \
    x; grynca::printGLError(#x, __FILE__, __LINE__);
#else
	#define GLCall(x) x
#endif

#endif //GLINCLUDE_H
