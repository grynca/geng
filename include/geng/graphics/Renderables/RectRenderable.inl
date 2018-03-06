#include "RectRenderable.h"
#include "../VertexData/Factories/geom_factories.h"

namespace grynca {

    inline Geom& RectRenderable::createNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint) {
        // static
        VertexDataP& verts = accWindow().getVertices().getFast<VertexDataP>();
        Geom& geom = verts.addItem(GL_TRIANGLE_FAN, usage_hint);
        FactoryRectTF<VertexDataP::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.add(Vec2{1,1}, norm_offset);
        return geom;
    }

    inline void RectRenderable::setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint) {
        setGeom(createNewGeom(norm_offset, usage_hint));
    }

    inline Vec2 RectRenderable::getGeomNormOffset()const {
        Geom& geom = const_cast<RectRenderable *>(this)->accRenderTaskPtr()->accGeom().acc();
        const FactoryRectTF<VertexDataP::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        return fact.getOffset(0);
    }

    inline Vec2 RectRenderable::getSize()const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().size;
    }

    inline Vec2 RectRenderable::getOffset()const {
        return getGeomNormOffset() * getSize();
    }

    inline void RectRenderable::setGeomNormOffset(const Vec2& offset) {
        Geom& geom = accRenderTaskPtr()->accGeom().acc();
        FactoryRectTF<VertexDataP::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.setOffset(0, offset);
    }

    inline void RectRenderable::setSize(const Vec2& size) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().size = size;
    }

    Vec2& RectRenderable::accSize() {
        return accRenderTaskPtr()->accDrawDataAs<DrawData>().size;
    }

    inline void RectRenderable::onBeforeDraw(Shader& s) {
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.transform *= Mat3::createScaleT(dd.size);

        SimpleColorShader& scs = (SimpleColorShader&)s;
        scs.setUniforms(dd);
    }
}