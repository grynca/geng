#include "Shaders.h"
#include "Shader.h"
#include "Window.h"
#include "glinclude.h"
#include "types/Type.h"
#include "types/Index.h"

namespace grynca {

    inline Shaders::Shaders(Window& w)
     : window_(&w), bound_id_(Index::Invalid())
    {}

    inline Shader* Shaders::getBoundShader() {
        if (bound_id_ == Index::Invalid())
            return NULL;
        return getById(bound_id_);
    }

    inline Window& Shaders::getWindow() {
        return *window_;
    }
}