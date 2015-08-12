#ifndef RECTSHADER_H
#define RECTSHADER_H

#include "../Shader.h"

namespace grynca {

    class RectShader : public Shader {
    public:
        RectShader() : Shader("RectShader", vsSrc(), fsSrc()) {
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_color = glGetUniformLocation(gl_handle_, "color");
            u_transform = glGetUniformLocation(gl_handle_, "transform");
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_color;
        GLint u_transform;
    private:
        static const std::string vsSrc() {
            return  R"(
            #version 330
            // inputs
            layout (location = 0) in vec2 v_pos;

            // uniforms
            uniform mat3 transform;
            uniform float z_coord;
            //uniform vec2 size;
            //uniform vec2 offset;

            // outputs
            out vec4 f_pos;

            void main() {
                vec3 trans_pos = transform*vec3(v_pos, 1.0);
                gl_Position =  vec4(trans_pos.xy, z_coord, trans_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return R"(
            #version 330
            // inputs
            in vec4 f_pos;

            // uniforms
            uniform vec4 color;

            // output to color buffer
            layout (location = 0) out vec4 f_color;

            void main() {
                f_color = color;
            }
            )";
        }
    };

}

#endif //RECTSHADER_H
