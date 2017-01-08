#ifndef PARTICLESHADER_H
#define PARTICLESHADER_H

#include "../Shader.h"

namespace grynca {

    class ParticleShader : public Shader {
    public:
        // UniformsBase::transform is actually VP transform (without model)
        struct Uniforms : public UniformsBase {
            Vec2 size;      // min, max
            Mat3 tr_transform;   // for transforming to correct texture region
            u32 texture;
        };

    public:
        ParticleShader()
         : Shader("ParticleShader", vsSrc(), fsSrc(), sizeof(Uniforms))
        {
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_p_size = glGetUniformLocation(gl_handle_, "p_size");
            u_texture = glGetUniformLocation(gl_handle_, "texture");
            u_tr_transform = glGetUniformLocation(gl_handle_, "tr_transform");
        }

        virtual void setUniforms(u8* uniforms) override {
            Uniforms* us = (Uniforms*)uniforms;

            setUniformMat3(u_transform, us->transform);
            setUniform1f(u_z_coord, us->z_coord);
            setUniform2f(u_p_size, us->size);
            setUniform1i(u_texture, us->texture);
            setUniformMat3(u_tr_transform, us->tr_transform);
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_transform;
        GLint u_p_size;
        GLint u_texture;
        GLint u_tr_transform;
    private:
        static const std::string vsSrc() {
            return  R"(
            #version 100
            precision mediump float;

            // inputs
            attribute vec4 v_pos_rot;       // pos, sin, cos
            attribute vec4 v_color_l;       // color RGB, life (0-1)

            // uniforms_
            uniform mat3 transform;
            uniform mat3 tr_transform;
            uniform float z_coord;
            uniform vec2 p_size;      // min, max

            // outputs
            varying vec4 f_color;
            varying mat3 f_tc_m;        // matrix for transforming texture coords from gl_PointCoord (local 0-1)

            void main() {
                float life = v_color_l.a;
                float alpha = 1.0 - abs(life*2.0 - 1.0);    // fade out
                f_color= vec4(v_color_l.rgb, alpha);

                mat3 local_t;
                local_t[0] = vec3(v_pos_rot.w, v_pos_rot.z, 0);
                local_t[1] = vec3(-v_pos_rot.z, v_pos_rot.w, 0);
                local_t[2] = vec3(0.5*(v_pos_rot.z-v_pos_rot.w), -0.5*(v_pos_rot.z+v_pos_rot.w), 1.0);

                f_tc_m = tr_transform * local_t;

                // EaseOutBack (p_size.z is coeff of overshoot)
                // commented out, is 2x slower with it
                //float t = life - 1.0;
                //gl_PointSize = p_size.x + p_size.y*(1.0-(t*t*((-(1.0+p_size.z)*t)-p_size.z)));

                gl_PointSize =  mix(p_size.x, p_size.y, life);
                vec3 trans_pos = transform*vec3(v_pos_rot.xy, 1.0);
                gl_Position =  vec4(trans_pos.xy, z_coord, trans_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return R"(
            #version 100
            precision mediump float;

            // inputs
            varying vec4 f_color;
            varying mat3 f_tc_m;

            // uniforms
            uniform sampler2D texture;

            void main() {
                vec3 tc = f_tc_m * vec3(gl_PointCoord.xy, 1.0);
                gl_FragColor = texture2D(texture, tc.xy) * f_color;
            }
            )";
        }
    };
}

#endif //PARTICLESHADER_H
