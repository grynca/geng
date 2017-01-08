#include "Vertices.h"
#include "VertexData/VertexData.h"
#include "types/Type.h"
#include "types/Index.h"

namespace grynca {

    inline Vertices::Vertices(Window& w)
     : window_(&w)
    {
    }


    inline void Vertices::update(f32 dt) {
        for (u32 i=0; i<getSize(); ++i) {
            VertexData* vd = getById(i);
            if (vd) {
                vd->update(dt);
            }
        }
    }

    inline Window& Vertices::getWindow() {
        return *window_;
    }

    inline std::string Vertices::getDebugString(u32 indent_cnt) {
        std::string indent = string_utils::spaces(indent_cnt);
        std::stringstream ss;
        for (u32 i=0; i<getSize(); ++i) {
            VertexData* vd = getById(i);
            if (vd) {
                ss << indent << vd->getDebugName_() << ":" << std::endl;
                ss << vd->getDebugString(indent_cnt+1);
            }
        }
        return ss.str();
    }
}