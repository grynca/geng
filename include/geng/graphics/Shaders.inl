#include "Shaders.h"
#include "Shaders/Shader.h"
#include "glinclude.h"
#include "types/Type.h"
#include "types/Index.h"

namespace grynca {

    inline Shaders::Shaders(Window& w)
     : window_(&w), bound_id_(InvalidId())
    {}

    inline Shader* Shaders::getBoundShader() {
        if (bound_id_ == InvalidId())
            return NULL;
        return getById(bound_id_);
    }

    inline Window& Shaders::getWindow() {
        return *window_;
    }

    inline std::string Shaders::getTypesDebugString()const {
        std::stringstream ss;
        ss << "Shader types:" << std::endl;
        for (u32 i=0; i<getSize(); ++i) {
            const Shader* s = tryGetById(i);
            if (s) {
                ss << " " << i << ": " << s->getName() << std::endl;
            }
        }
        return ss.str();
    }
}