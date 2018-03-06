#ifndef SHADER_H
#define SHADER_H

#include "types/containers/fast_vector.h"
#include "maths/Vec2.h"
#include "maths/Mat3.h"
#include "../glinclude.h"
#include <string>

namespace grynca {

    // fw
    class RenderTask;
    class Shaders;

    class Shader : public ManagedItemSingleton<Shaders> {
    public:
        // binding vertex attrib names to ids(pos in array)
        static const fast_vector<const char*>& getVertexAttribs() {
            static fast_vector<const char*> va = {
                    "v_pos",
                    "v_color",
                    "v_pos_uv",
                    "v_pos_rot",
                    "v_color_l"
            };
            return va;
        }
    public:
        virtual ~Shader();

        const std::string& getName()const;
        const ustring& getLinkingLog();
        const fast_vector<ustring>& getCompilationLogs();

        u32 getGLHandle()const;

        void setUniform1f(const std::string& name, f32 value);
        void setUniform1fv(const std::string& name, const f32* value, int count);
        void setUniform1i(const std::string& name, int value);
        void setUniform1iv(const std::string& name, const int* value, int count);
        void setUniform2f(const std::string& name, const Vec2& vector);
        void setUniformMat3(const std::string& name, const Mat3& matrix);
        void setUniform4fv(const std::string& name, const f32* value, int count);
        void setUniform3fv(const std::string& name, const f32* value, int count);

        void setUniform1f(GLint loc, f32 value);
        void setUniform1fv(GLint loc, const f32* value, int count);
        void setUniform1i(GLint loc, int value);
        void setUniform1iv(GLint loc, const int* value, int count);
        void setUniform2f(GLint loc, const Vec2& vector);
        void setUniformMat3(GLint loc, const Mat3& matrix);
        void setUniform4fv(GLint loc, const f32* value, int count);
        void setUniform3fv(GLint loc, const f32* value, int count);

        void bind();

        static u32 getVertexAttribId(const char* name);
    protected:
        Shader(const std::string& name, const std::string& vs_src, const std::string& fs_src);

        GLuint compileShaderSource_(const char* src, GLenum shader_type, std::string& compile_log);
        GLint getUniformLocation_(const std::string& name);

        GLuint gl_handle_;
        std::string name_;
        fast_vector<ustring> compilation_logs_;
        ustring linking_log_;
    };
}

#include "Shader.inl"
#endif //SHADER_H
