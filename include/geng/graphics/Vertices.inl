#include "Vertices.h"
#include "VertexData.h"
#include "Window.h"
#include "types/Type.h"

namespace grynca {

    inline Vertices::Vertices(Window& w)
     : window_(&w), bound_id_(uint32_t(-1))
    {}


    inline void Vertices::syncWithGPU() {
        for (uint32_t i=0; i<getSize(); ++i) {
            VertexData* vd = getById(i);
            if (vd)
                vd->syncWithGPU();
        }
    }

    inline VertexData* Vertices::getBoundVertexData() {
        if (bound_id_ == uint32_t(-1))
            return NULL;
        return getById(bound_id_);
    }

    inline Window& Vertices::getWindow() {
        return *window_;
    }
}