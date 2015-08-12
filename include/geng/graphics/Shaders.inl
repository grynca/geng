#include "Shaders.h"
#include "Shader.h"
#include "Window.h"
#include "glinclude.h"
#include "types/Type.h"

namespace grynca {

    inline Shaders::Shaders(Window& w)
     : window_(&w), bound_id_(uint32_t(-1))
    {}

    inline Shader* Shaders::getBoundShader() {
        if (bound_id_ == uint32_t(-1))
            return NULL;
        return getById(bound_id_);
    }

    inline Window& Shaders::getWindow() {
        return *window_;
    }
}