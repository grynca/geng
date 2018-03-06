#ifndef SPRITESHADER_H
#define SPRITESHADER_H

#include "Shader.h"

namespace grynca {

    class SimpleTexturedShader : public Shader {
    public:
        SimpleTexturedShader()
         : Shader("SimpleTexturedShader", vsSrc(), fsSrc())
        {
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_color = glGetUniformLocation(gl_handle_, "color");
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_texture = glGetUniformLocation(gl_handle_, "texture");
        }

        template <typename DD>
        void setUniforms(const DD& draw_data) {
            setUniformMat3(u_transform, draw_data.transform);
            setUniform1f(u_z_coord, draw_data.z_coord);
            setUniform4fv(u_color, draw_data.color.c_, 1);
            setUniform1i(u_texture, draw_data.texture);
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_transform;
        GLint u_color;
        GLint u_texture;
    private:

        static const std::string vsSrc() {
            return  R"(
            #version 100
            precision mediump float;

            // inputs
            attribute vec4 v_pos_uv;

            // uniforms_
            uniform mat3 transform;
            uniform float z_coord;

            // outputs
            varying vec2 uv_fs;

            void main()
            {
                uv_fs = v_pos_uv.zw;
                vec3 transformed_pos = transform*vec3(v_pos_uv.xy, 1.0);
                gl_Position =  vec4(transformed_pos.xy, z_coord, transformed_pos.z);
            }
            )";
        }

        static const std::string fsSrc() {
            return  R"(
            #version 100
            precision mediump float;

            // inputs
            varying vec2 uv_fs;

            // uniforms_
            uniform vec4 color;
            uniform sampler2D texture;

            void main()
            {
               gl_FragColor = color*texture2D(texture, uv_fs);
            }
            )";
        }
    };
}

#endif //SPRITESHADER_H
