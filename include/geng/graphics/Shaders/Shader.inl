#include "Shader.h"
#include "types/Index.h"
#include "../Shaders.h"
#include "../graphics_config.h"
#include <glm/gtc/type_ptr.hpp>

namespace grynca {

    inline const std::string& Shader::getName()const {
        return name_;
    }

    inline const ustring& Shader::getLinkingLog() {
        return linking_log_;
    }

    inline const fast_vector<ustring>& Shader::getCompilationLogs() {
        return compilation_logs_;
    }

    inline u32 Shader::getGLHandle()const {
        return gl_handle_;
    }

    inline void Shader::setUniform1f(const std::string& name, f32 value) {
        setUniform1f(getUniformLocation_(name), value);
    }

    inline void Shader::setUniform1fv(const std::string& name, const f32* value, int count) {
        setUniform1fv(getUniformLocation_(name), value, count);
    }

    inline void Shader::setUniform1i(const std::string& name, int value) {
        setUniform1i(getUniformLocation_(name), value);
    }

    inline void Shader::setUniform1iv(const std::string& name, const int* value, int count) {
        setUniform1iv(getUniformLocation_(name), value, count);
    }

    inline void Shader::setUniform2f(const std::string& name, const Vec2& vector) {
        setUniform2f(getUniformLocation_(name), vector);
    }

    inline void Shader::setUniformMat3(const std::string& name, const Mat3& matrix) {
        setUniformMat3(getUniformLocation_(name), matrix);
    }

    inline void Shader::setUniform4fv(const std::string& name, const f32* value, int count) {
        setUniform4fv(getUniformLocation_(name), value, count);
    }

    inline void Shader::setUniform3fv(const std::string& name, const f32* value, int count) {
        setUniform3fv(getUniformLocation_(name), value, count);
    }

    inline void Shader::setUniform1f(GLint loc, f32 value) {
        GLCall(glUniform1f(loc, value));
    }

    inline void Shader::setUniform1fv(GLint loc, const f32* value, int count) {
        GLCall(glUniform1fv(loc, count, value));
    }

    inline void Shader::setUniform1i(GLint loc, int value) {
        GLCall(glUniform1i(loc, value));
    }

    inline void Shader::setUniform1iv(GLint loc, const int* value, int count) {
        GLCall(glUniform1iv(loc, count, value));
    }

    inline void Shader::setUniform2f(GLint loc, const Vec2& vector) {
        GLCall(glUniform2f(loc, vector.getX(), vector.getY()));
    }

    inline void Shader::setUniformMat3(GLint loc, const Mat3& matrix) {
        GLCall(glUniformMatrix3fv(loc, 1, (GLboolean)false, glm::value_ptr(matrix.getInternal())));
    }

    inline void Shader::setUniform4fv(GLint loc, const f32* value, int count) {
        GLCall(glUniform4fv(loc, count, value));
    }

    inline void Shader::setUniform3fv(GLint loc, const f32* value, int count) {
        GLCall(glUniform3fv(loc, count, value));
    }

    inline void Shader::bind() {
        GLCall(glUseProgram(getGLHandle()));
        getManager().bound_id_ = getId();
    }

    inline u32 Shader::getVertexAttribId(const char* name) {
        // static
        for (u32 i=0; i< getVertexAttribs().size(); ++i) {
            if (strcmp(name, getVertexAttribs()[i]) == 0)
                return i;
        }
        NEVER_GET_HERE("Unknown vertex attrib.");
        return InvalidId();
    }

    inline Shader::Shader(const std::string& name, const std::string& vs_src, const std::string& fs_src)
     : name_(name)
    {
        gl_handle_ = GLCall(glCreateProgram());
        if (!gl_handle_)
            throw GL_Exception((name_ + ": glCreateProgram() failed").c_str());

        std::string vs_log, fs_log;
        GLuint vs_handle = compileShaderSource_(vs_src.c_str(), GL_VERTEX_SHADER, vs_log);
        if (vs_handle == InvalidId()) {
            dout(vs_log << std::endl);
            throw GL_Exception((name_ + ": GL_VERTEX_SHADER glCompileShader() failed.").c_str());
        }
        GLuint fs_handle = compileShaderSource_(fs_src.c_str(), GL_FRAGMENT_SHADER, fs_log);
        if (fs_handle == InvalidId()) {
            dout(fs_log << std::endl);
            throw GL_Exception((name_ + ": GL_FRAGMENT_SHADER glCompileShader() failed.").c_str());
        }
        compilation_logs_.emplace_back(vs_log);
        compilation_logs_.emplace_back(fs_log);
        // attach compiled parts to program
        GLCall(glAttachShader(gl_handle_, vs_handle));
        GLCall(glAttachShader(gl_handle_, fs_handle));

        // bind vertex attribs
        for (u32 i=0; i<getVertexAttribs().size(); ++i) {
            GLCall(glBindAttribLocation(gl_handle_, i, getVertexAttribs()[i]));
        }

        // link shader program
        GLCall(glLinkProgram(gl_handle_));

        // getTransform linking log
        std::string ll;
        int length;
        GLCall(glGetProgramiv(gl_handle_, GL_INFO_LOG_LENGTH, &length));
        ll.resize((unsigned int)length);
        GLCall(glGetProgramInfoLog(gl_handle_, length, NULL, &ll[0]));
        linking_log_ = ll;

        // getTransform linking status
        int status;
        GLCall(glGetProgramiv(gl_handle_, GL_LINK_STATUS, &status));
        if(status == GL_FALSE) {
            dout(linking_log_ << std::endl);
            throw GL_Exception((name + ": glLinkProgram() failed.").c_str());
        }

        // detach and delete shader parts
        GLCall(glDetachShader(gl_handle_, vs_handle));
        GLCall(glDetachShader(gl_handle_, fs_handle));
        GLCall(glDeleteShader(vs_handle));
        GLCall(glDeleteShader(fs_handle));
    }

    inline Shader::~Shader() {
        GLCall(glDeleteProgram(gl_handle_));
    }

    inline GLuint Shader::compileShaderSource_(const char* src, GLenum shader_type, std::string& compile_log) {
        GLuint gl_handle= GLCall(glCreateShader(shader_type));
        if (!gl_handle)
            throw GL_Exception("glCreateShader() failed.");
        GLCall(glShaderSource(gl_handle, 1, &src, NULL)); // load source to opengl
        GLCall(glCompileShader(gl_handle));       // compile

        // getTransform compilation log
        int length;
        GLCall(glGetShaderiv(gl_handle, GL_INFO_LOG_LENGTH, &length));      // getTransform log length
        compile_log.resize((unsigned int)length);
        GLCall(glGetShaderInfoLog(gl_handle, length, NULL, &compile_log[0]));   // getTransform log string

        // getTransform compile status
        int status;
        GLCall(glGetShaderiv(gl_handle, GL_COMPILE_STATUS, &status));
        if(status == GL_FALSE)
            return InvalidId();
        else
            return gl_handle;
    }

    inline GLint Shader::getUniformLocation_(const std::string& name) {
        return GLCall(glGetUniformLocation(gl_handle_, name.c_str()));
    }

}
