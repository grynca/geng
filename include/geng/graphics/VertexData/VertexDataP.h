#ifndef VERTEXDATAP_H
#define VERTEXDATAP_H

#include "maths/Vec2.h"
#include "../VertexData.h"

namespace grynca {

    class VertexDataP : public VertexData {
    public:
        // used for shapes
        struct Vertex {
            Vec2 pos;
        };

        VertexDataP() {
            setVertexAttribs<Vertex>({{2, GL_FLOAT, false, 0}});

            // create shared unit quad geom
            Geom& geom = addItem(GL_TRIANGLE_FAN);
            geom.addVertex(VertexDataP::Vertex{{ -0.5, -0.5}});
            geom.addVertex(VertexDataP::Vertex{{  0.5, -0.5}});
            geom.addVertex(VertexDataP::Vertex{{  0.5,  0.5}});
            geom.addVertex(VertexDataP::Vertex{{ -0.5,  0.5}});
            unit_quad_geom_ref_ = geom;
        }

        Geom& getUnitQuadGeom() {
            return unit_quad_geom_ref_.get();
        }

    private:
        VertexData::ItemRef unit_quad_geom_ref_;
    };
}

#endif //VERTEXDATAP_H
