#ifndef SHADER_H
#define SHADER_H

#include "types/containers/fast_vector.h"
#include "Shaders.h"
#include "maths/Vec2.h"
#include "maths/Mat3.h"
#include "glinclude.h"
#include <string>

namespace grynca {

    class Shader : public ManagedItem<Shaders> {
    public:
        virtual ~Shader();

        const std::string& getLinkingLog();
        const fast_vector<std::string>& getCompilationLogs();

        uint32_t getGLHandle()const;

        void setUniform1f(const std::string& name, float value);
        void setUniform1fv(const std::string& name, float* value, int count);
        void setUniform1i(const std::string& name, int value);
        void setUniform1iv(const std::string& name, int* value, int count);
        void setUniform2f(const std::string& name, const Vec2& vector);
        void setUniformMat3(const std::string& name, const Mat3& matrix);
        void setUniform4fv(const std::string& name, float* value, int count);

        void setUniform1f(GLint loc, float value);
        void setUniform1fv(GLint loc, float* value, int count);
        void setUniform1i(GLint loc, int value);
        void setUniform1iv(GLint loc, int* value, int count);
        void setUniform2f(GLint loc, const Vec2& vector);
        void setUniformMat3(GLint loc, const Mat3& matrix);
        void setUniform4fv(GLint loc, float* value, int count);

        void bind();
    protected:
        Shader(const std::string& name, const std::string& vs_src, const std::string& fs_src);      // creates vertex & fragment shader program

        GLuint compileShaderSource_(const char* src, GLenum shader_type, std::string& compile_log);
        GLint getUniformLocation_(const std::string& name);

        GLuint gl_handle_;
        std::string name_;
        fast_vector<std::string> compilation_logs_;
        std::string linking_log_;
    };
}

#endif //SHADER_H
