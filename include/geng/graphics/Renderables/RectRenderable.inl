#include "RectRenderable.h"
#include "../VertexData/Factories/geom_factories.h"

namespace grynca {

    inline VertexData::ItemRef RectRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataP& verts = w.getVertices().get<VertexDataP>();
        FactoryRectTF<VertexDataP::Vertex> fact = verts.addWithFactory<FactoryRectTF<VertexDataP::Vertex> >(GeomState::stNone, usage_hint);
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        return fact.getGeom();
    }

    inline Vec2 RectRenderable::getSize()const {
        return getRenderTask()->getLocalTransform().getScale();
    }

    inline Vec2 RectRenderable::getGeomNormOffset()const {
        Geom& geom = const_cast<RectRenderable *>(this)->getRenderTask()->getGeom().get();
        const FactoryRectTF<VertexDataP::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        return fact.getOffset(0);
    }

    inline Vec2& RectRenderable::accSize() {
        return accRenderTask()->accLocalTransform().accScale();
    }

    inline RectRenderable& RectRenderable::setColor(const Colorf& clr) {
        PgonRenderable::setColor(clr);
        return *this;
    }

    inline RectRenderable& RectRenderable::setSize(const Vec2& size) {
        accRenderTask()->accLocalTransform().setScale(size);
        return *this;
    }

    inline RectRenderable& RectRenderable::setGeomNormOffset(const Vec2& offset) {
        Geom& geom = getRenderTask()->getGeom().get();
        FactoryRectTF<VertexDataP::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataP::Vertex> >();
        fact.setOffset(0, offset);
        return *this;
    }
}