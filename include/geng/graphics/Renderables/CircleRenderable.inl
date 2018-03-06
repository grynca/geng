#include "CircleRenderable.h"
#include "../Shaders/CircleShader.h"
#include "../VertexData/VertexDataP.h"

namespace grynca {

    inline void CircleRenderable::setNewGeom(GeomUsageHint usage_hint) {
        VertexDataP& verts = accWindow().getVertices().getFast<VertexDataP>();
        FactoryRectTF<VertexDataP::Vertex> fact = verts.addWithFactory<FactoryRectTF<VertexDataP::Vertex> >(usage_hint);
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        setGeom(fact.getGeom());
    }

    inline void CircleRenderable::setStaticSharedGeom() {
        VertexDataP& verts = accWindow().getVertices().getFast<VertexDataP>();
        render_task_ptr_->setGeom(verts.accSharedUnitQuadGeom(NormOffset::otCenter));
    }

    inline f32 CircleRenderable::getInnerRadius()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().r_range.getX();
    }

    inline f32 CircleRenderable::getOuterRadius()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().r_range.getY();
    }

    inline Colorf CircleRenderable::getColor()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().color;
    }

    inline void CircleRenderable::setColor(const Colorf& c) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().color = c;
    }

    inline void CircleRenderable::setInnerRadius(f32 inner_r) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().r_range.setX(inner_r);
    }

    inline void CircleRenderable::setOuterRadius(f32 outer_r) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().r_range.setY(outer_r);
    }

    inline void CircleRenderable::onBeforeDraw(Shader& s) {
        CircleShader& cs = (CircleShader&)s;
        cs.setUniforms(accRenderTaskPtr()->getDrawDataAs<DrawData>());
    }
}