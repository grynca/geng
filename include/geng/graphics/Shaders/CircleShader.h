#ifndef SHAPESSHADER_H
#define SHAPESSHADER_H

#include "Shader.h"

namespace grynca {

    class CircleShader : public Shader {
    public:
        CircleShader()
         : Shader("CircleShader", vsSrc(), fsSrc())
        {
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_color = glGetUniformLocation(gl_handle_, "color");
            u_r_range = glGetUniformLocation(gl_handle_, "r_range");
        }

        template <typename DD>
        void setUniforms(const DD& draw_data) {
            setUniformMat3(u_transform, draw_data.transform);
            setUniform1f(u_z_coord, draw_data.z_coord);
            setUniform2f(u_r_range, draw_data.r_range );
            setUniform4fv(u_color, draw_data.color.c_, 1);
        }

        // uniform locations
        GLint u_color;
        GLint u_r_range;
        GLint u_z_coord;
        GLint u_transform;
    private:
        static const std::string vsSrc() {
            return
#ifdef WEB
            R"(
            #version 100
            )"
#else
            R"(
            #version 130
            )"
#endif
            R"(
            precision mediump float;

            // inputs
            attribute vec2 v_pos;

            // uniforms_
            uniform mat3 transform;
            uniform float z_coord;
            uniform vec2 r_range;

            // outputs
            varying vec2 f_pos;

            void main() {
                vec2 pos = v_pos*r_range.y*2.0;
                f_pos = pos;
                vec3 trans_pos = transform*vec3(pos, 1.0);
                gl_Position =  vec4(trans_pos.xy, z_coord, trans_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return
#ifdef WEB
            R"(
            #version 100
            #extension GL_OES_standard_derivatives : enable     // needed for webgl to enable fwidth
            )"
#else
            R"(
            #version 130
            )"
#endif
            R"(
            precision mediump float;

            // inputs
            varying vec2 f_pos;

            // uniforms_
            uniform vec4 color;
            uniform vec2 r_range;

            void main() {
                float dist = length(f_pos);
                float delta = 2.0*fwidth(f_pos.x);

                float r_from = r_range.x;
                float r_to = r_range.y;
                float alpha2 = smoothstep(r_from-delta, r_from, dist);
                float alpha1 = smoothstep(r_to-delta, r_to, dist);
                float alpha = abs(alpha1-alpha2);

                gl_FragColor = vec4(color.xyz, mix(0.0, color.w, alpha));
            }
            )";
        }
    };
}

#endif //SHAPESSHADER_H
