#ifndef GLINCLUDE_H
#define GLINCLUDE_H

#include "functions/ssu.h"
#include "types/Exception.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

namespace grynca {

    static std::string GLErrorString(GLenum err_code) {
        std::string err_s = "[" +ssu::toStringA(err_code)+ "]";
#ifndef WEB
        // emscripten does not have gluErrorString()
        err_s += std::string(": ")+(const char*)gluErrorString(err_code);
#endif
        return err_s;
    }

    static std::string GlewErrorString(GLenum err_code) {
        std::string err_s = "[" +ssu::toStringA(err_code)+ "]";
#ifndef WEB
        err_s += std::string(": ")+(const char*)glewGetErrorString(err_code);
#endif
        return err_s;
    }


    inline static void printGLError(const char* function, const char* file, int line) {
        GLenum err_code;
        if ((err_code=glGetError())!=GL_NO_ERROR) {
            std::cerr << "(" << file << ":" << line << ") " << function << ": " << grynca::GLErrorString(err_code) << std::endl;
        }
    }

    struct GL_Exception : public Exception
    {
        GL_Exception() throw()
                : Exception(std::string("OpenGL : ") + GLErrorString(glGetError())) {}

        GL_Exception(const char * text) throw()
                : Exception(std::string("OpenGL : ") + text + " " + GLErrorString(glGetError())) {}
    };

    struct GLEW_Exception : public Exception
    {
        GLEW_Exception(u32 error) throw()
                : Exception(std::string("GLEW : ") + GlewErrorString(error) ) {}

        GLEW_Exception(const char * text, u32 error) throw()
                : Exception(std::string("GLEW : ") + text + GlewErrorString(error)) {}
    };

}

#ifndef NDEBUG
#define GLCall(x) \
    x; grynca::printGLError(#x, __FILE__, __LINE__);
#else
	#define GLCall(x) x
#endif

#endif //GLINCLUDE_H
