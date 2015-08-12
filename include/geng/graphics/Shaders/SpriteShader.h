#ifndef SPRITESHADER_H
#define SPRITESHADER_H

#include "../Shader.h"

namespace grynca {

    class SpriteShader : public Shader {
    public:
        SpriteShader() : Shader("SpriteShader", vsSrc(), fsSrc()) {
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
            #version 330
            // inputs
            layout (location = 0) in vec4 pos_uv;

            // uniforms
            uniform mat3 transform;
            uniform float z_coord;
            // outputs
            out vec2 uv_fs;

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
            #version 330
            // inputs
            in vec2 uv_fs;

            // uniforms
            uniform sampler2D texture;

            // output to color buffer
            layout (location = 0) out vec4 frag_color;

            void main()
            {
               frag_color = texture2D(texture, uv_fs);
            }
            )";
        }
    };


}

#endif //SPRITESHADER_H
