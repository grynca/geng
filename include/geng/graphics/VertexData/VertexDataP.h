#ifndef VERTEXDATAP_H
#define VERTEXDATAP_H

#include "maths/Vec2.h"
#include "VertexData.h"

namespace grynca {

    class VertexDataP : public VertexData {
    public:
        // used for shapes
        struct Vertex {
            Vec2 pos;
        };

        VertexDataP()
         : VertexData("VertexDataP")
        {
            setVertexLayout<Vertex>({{Shader::getVertexAttribId("v_pos"), 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos)}});
            initSharedQuadGeomPositions<Vertex>();
        }
    };
}

#endif //VERTEXDATAP_H
