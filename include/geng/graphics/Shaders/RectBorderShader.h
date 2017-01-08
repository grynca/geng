#ifndef RECTBORDERSHADER_H
#define RECTBORDERSHADER_H

#include "../Shader.h"

namespace grynca {

    class RectBorderShader : public Shader {
    public:
        struct Uniforms : public UniformsBase {
            Colorf color;
            Vec2 borders;
            Vec2 offset;
        };
    public:
        RectBorderShader()
         : Shader("RectBorderShader", vsSrc(), fsSrc(), sizeof(Uniforms))
        {
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_color = glGetUniformLocation(gl_handle_, "color");
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_borders = glGetUniformLocation(gl_handle_, "borders");
            u_offset = glGetUniformLocation(gl_handle_, "offset");
        }

        virtual void setUniforms(u8* uniforms) override {
            Uniforms* us = (Uniforms*)uniforms;

            setUniformMat3(u_transform, us->transform);
            setUniform1f(u_z_coord, us->z_coord);
            setUniform4fv(u_color, us->color.c_, 1);
            setUniform2f(u_borders, us->borders);
            setUniform2f(u_offset, us->offset);
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_color;
        GLint u_transform;
        GLint u_borders;
        GLint u_offset;
    private:

        static const std::string vsSrc() {
            return  R"(
            #version 100
            precision mediump float;

            // inputs
            attribute vec2 v_pos;

            // outputs
            varying vec2 pos_norm;      // from 0..1

            // uniforms_
            uniform mat3 transform;
            uniform float z_coord;
            uniform vec2 offset;

            void main() {
                pos_norm = v_pos - offset;
                vec3 trans_pos = transform*vec3(v_pos, 1.0);
                gl_Position =  vec4(trans_pos.xy, z_coord, trans_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return R"(
            #version 100
            precision mediump float;

            // inputs
            varying vec2 pos_norm;

            // uniforms
            uniform vec4 color;
            uniform vec2 borders;

            // returns 1.0 when < 0.0
            // else 0.0
            float lessThanZero(float v) {
                return clamp(-sign(v), 0.0, 1.0);
            }

            void main() {
                float left_b = pos_norm.x - borders.x;
                float top_b = pos_norm.y - borders.y;
                float right_b = (1.0 - pos_norm.x) - borders.x;
                float bot_b = (1.0 - pos_norm.y) - borders.y;
                float m = min(left_b, min(top_b, min(right_b, bot_b)));
                // when m < 0 ... pixel is in border,
                // else       ... pixel is inside and is transparent
                float ltz = lessThanZero(m);

                gl_FragColor = vec4(color.xyz, mix(0.0, color.w, ltz));
            }
            )";
        }
    };

}

#endif //RECTBORDERSHADER_H
