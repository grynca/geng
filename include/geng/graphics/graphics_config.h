#ifndef GRAPHICS_CONFIG_H
#define GRAPHICS_CONFIG_H

#include <stdint.h>

namespace grynca {
    namespace config {
        static constexpr bool START_FULLSCREEN = false;

        // bits in packed id for renderable, together must be 31
        static constexpr u16 LAYER_BITS = 8;
        static constexpr u16 SHADER_BITS = 8;
        static constexpr u16 VERT_LAYOUT_BITS = 7;
        static constexpr u16 VBO_BITS = 8;

        static constexpr u16 MAX_LAYERS = (1<<LAYER_BITS);
        static constexpr u16 MAX_SHADERS = (1<<SHADER_BITS);
        static constexpr u16 MAX_VERTEX_LAYOUTS = (1<<VERT_LAYOUT_BITS);
        static constexpr u16 MAX_VBOS = (1<<VBO_BITS);     // for each vertex layout

        static constexpr u32 INITIAL_VBO_SIZE = kilobytes(1024);
        static constexpr u32 SHADER_UNIFORMS_SIZE = 88;
        static constexpr u32 PARTICLES_MAX = kilobytes(32);
    }
}

#endif //GRAPHICS_CONFIG_H
