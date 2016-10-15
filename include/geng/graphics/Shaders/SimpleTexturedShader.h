#ifndef SPRITESHADER_H
#define SPRITESHADER_H

#include "../Shader.h"

namespace grynca {

    class SimpleTexturedShader : public Shader {
    public:
        SimpleTexturedShader() : Shader("SimpleTexturedShader", vsSrc(), fsSrc()) {
            u_z_coord = glGetUniformLocation(gl_handle_, "z_coord");
            u_transform = glGetUniformLocation(gl_handle_, "transform");
            u_texture = glGetUniformLocation(gl_handle_, "texture");
        }

        // uniform locations
        GLint u_z_coord;
        GLint u_transform;
        GLint u_texture;
    private:

        static const std::string vsSrc() {
            return  R"(
            #version 100
            precision mediump float;

            // inputs
            attribute vec4 pos_uv;

            // uniforms
            uniform mat3 transform;
            uniform float z_coord;

            // outputs
            varying vec2 uv_fs;

            void main()
            {
                uv_fs = pos_uv.zw;
                vec3 transformed_pos = transform*vec3(pos_uv.xy, 1.0);
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

            // uniforms
            uniform sampler2D texture;

            void main()
            {
               gl_FragColor = texture2D(texture, uv_fs);
            }
            )";
        }
    };
}

#endif //SPRITESHADER_H
