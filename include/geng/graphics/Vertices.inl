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

    inline std::string Vertices::getTypesDebugString()const {
        std::stringstream ss;
        ss << "VertexData:" << std::endl;
        for (u32 i=0; i<getSize(); ++i) {
            const VertexData *vd = tryGetById(i);
            if (vd) {
                ss << " " << i << ": " << vd->getName() << std::endl;
            }
        }
        return ss.str();
    }

    inline std::string Vertices::getDebugString(u32 indent_cnt)const {
        std::string indent = ssu::spacesA(indent_cnt);
        std::stringstream ss;
        for (u32 i=0; i<getSize(); ++i) {
            const VertexData* vd = tryGetById(i);
            if (vd) {
                ss << indent << vd->getName() << " [v_size: " <<  vd->getVertexSize() << "b]:" << std::endl;
                ss << vd->getDebugString(indent_cnt+1);
            }
        }
        return ss.str();
    }
}