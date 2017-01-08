#include "CircleRenderable.h"
#include "../Shaders/CircleShader.h"
#include "../VertexData/VertexDataP.h"

namespace grynca {

    inline VertexData::ItemRef CircleRenderable::createNewGeom(Window& w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataP& verts = w.getVertices().get<VertexDataP>();
        if (usage_hint == GeomState::uhStatic) {
            return verts.getSharedQuadCenter().get();
        }
        // else
        FactoryRectTF<VertexDataP::Vertex> fact = verts.addWithFactory<FactoryRectTF<VertexDataP::Vertex> >(GeomState::stNone, usage_hint);
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        return fact.getGeom();
    }

    inline CircleRenderable::CircleRenderable(const Renderer2D::ItemRef& rt)
      : Renderable(rt)
    {}

    inline f32 CircleRenderable::getInnerRadius()const {
        return getRenderTask()->getUniformsAs<CircleShader::Uniforms>().r_range.getX();
    }

    inline f32 CircleRenderable::getOuterRadius()const {
        return getRenderTask()->getUniformsAs<CircleShader::Uniforms>().r_range.getY();
    }

    inline Colorf CircleRenderable::getColor()const {
        return getRenderTask()->getUniformsAs<CircleShader::Uniforms>().color;
    }

    inline const Geom& CircleRenderable::getGeom()const {
        return getWindow().getVertices().get<VertexDataP>().getSharedQuadCenter().get();
    }

    inline CircleRenderable& CircleRenderable::setColor(const Colorf& c) {
        accRenderTask()->getUniformsAs<CircleShader::Uniforms>().color = c;
        return *this;
    }

    inline CircleRenderable& CircleRenderable::setInnerRadius(f32 inner_r) {
        accRenderTask()->getUniformsAs<CircleShader::Uniforms>().r_range.setX(inner_r);
        return *this;
    }

    inline CircleRenderable& CircleRenderable::setOuterRadius(f32 outer_r) {
        accRenderTask()->getUniformsAs<CircleShader::Uniforms>().r_range.setY(outer_r);
        return *this;
    }

    inline CircleRenderable& CircleRenderable::setPosition(const Vec2& pos) {
        accRenderTask()->accLocalTransform().setPosition(pos);
        return *this;
    }
}