#ifndef SHAPESSHADER_H
#define SHAPESSHADER_H

#include "../Shader.h"

namespace grynca {

    class CircleShader : public Shader {
    public:
        CircleShader() : Shader("CircleShader", vsSrc(), fsSrc()) {
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_color = glGetUniformLocation(gl_handle_, "color");
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_r_range = glGetUniformLocation(gl_handle_, "r_range");
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_color;
        GLint u_transform;
        GLint u_r_range;
    private:
        static const std::string vsSrc() {
            return  R"(
            #version 330
            // inputs
            layout (location = 0) in vec2 v_pos;

            // uniforms
            uniform mat3 transform;
            uniform float z_coord;
            uniform vec2 r_range;

            // outputs
            out vec2 f_pos;

            void main() {
                vec2 pos = v_pos*r_range.y*2;
                f_pos = pos;
                vec3 trans_pos = transform*vec3(pos, 1.0);
                gl_Position =  vec4(trans_pos.xy, z_coord, trans_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return R"(
            #version 330
            // inputs
            in vec2 f_pos;

            // uniforms5
            uniform vec4 color;
            uniform vec2 r_range;

            // output to color buffer
            layout (location = 0) out vec4 f_color;

            void main() {
                float dist = length(f_pos);
                float delta = 2*fwidth(f_pos.x);

                float r_from = r_range.x;
                float r_to = r_range.y;
                float alpha2 = smoothstep(r_from-delta, r_from, dist);
                float alpha1 = smoothstep(r_to-delta, r_to, dist);
                float alpha = abs(alpha1-alpha2);

                f_color = vec4(color.xyz, mix(0, color.w, alpha));
            }
            )";
        }
    };

}

#endif //SHAPESSHADER_H
