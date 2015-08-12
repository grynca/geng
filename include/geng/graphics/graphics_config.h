#ifndef GRAPHICS_CONFIG_H
#define GRAPHICS_CONFIG_H

#include <stdint.h>

namespace grynca {
    namespace config {
        static constexpr bool START_FULLSCREEN = false;
        static constexpr uint32_t GLVER_MAJOR = 3;
        static constexpr uint32_t GLVER_MINOR = 3;

        static constexpr uint32_t MAX_LAYERS = 256;
    }
}

#endif //GRAPHICS_CONFIG_H
