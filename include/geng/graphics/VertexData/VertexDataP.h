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

        VertexDataP() {
            setVertexLayout<Vertex>({{Shader::getVertexAttribId("v_pos"), 2, GL_FLOAT, false, sizeof(Vertex), offsetof(Vertex, pos)}});

            // create shared unit quad geom
            VertexData::ItemRef geom = addItem(GL_TRIANGLE_FAN, GeomState::stNone, GeomState::uhStatic);
            geom->addVertex(VertexDataP::Vertex{{ -0.5, -0.5}});
            geom->addVertex(VertexDataP::Vertex{{  0.5, -0.5}});
            geom->addVertex(VertexDataP::Vertex{{  0.5,  0.5}});
            geom->addVertex(VertexDataP::Vertex{{ -0.5,  0.5}});
            shared_geom_center_ = geom;

            geom = addItem(GL_TRIANGLE_FAN, GeomState::stNone, GeomState::uhStatic);
            geom->addVertex(VertexDataP::Vertex{{ 0, 0}});
            geom->addVertex(VertexDataP::Vertex{{ 1, 0}});
            geom->addVertex(VertexDataP::Vertex{{ 1, 1}});
            geom->addVertex(VertexDataP::Vertex{{ 0, 1}});
            shared_geom_lt_ = geom;
        }

        VertexData::ItemRef& getSharedQuadCenter() {
            return shared_geom_center_;
        }

        VertexData::ItemRef& getSharedQuadLT() {
            return shared_geom_lt_;
        }

    private:
        virtual std::string getDebugName_() override { return "VertexDataP"; }

        VertexData::ItemRef shared_geom_center_;
        VertexData::ItemRef shared_geom_lt_;
    };
}

#endif //VERTEXDATAP_H
