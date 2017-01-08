#include "SpriteRenderable.h"
#include "../VertexData/Factories/geom_factories.h"
#include "../VertexData/SpriteAnimationStates.h"

namespace grynca {

    inline VertexData::ItemRef SpriteRenderable::createNewGeom(Window &w, GeomState::UsageHint usage_hint) {
        // static
        VertexDataPT &verts = w.getVertices().get<VertexDataPT>();
        FactoryRectTF<VertexDataPT::Vertex> fact = verts.addWithFactory<FactoryRectTF<VertexDataPT::Vertex> >(
                GeomState::stNone, usage_hint);
        fact.add(Vec2(1, 1), Vec2(-0.5f, -0.5f));
        return fact.getGeom();
    }

    inline bool SpriteRenderable::getAnimated() const {
        Geom &geom = getRenderTask()->getGeom().get();
        return geom.getGeomStateType() == GeomState::stAnimation;
    }

    inline Vec2 SpriteRenderable::getSize() const {
        return getRenderTask()->getLocalTransform().getScale();
    }

    inline Vec2 SpriteRenderable::getGeomNormOffset() const {
        Geom &geom = const_cast<SpriteRenderable *>(this)->getRenderTask()->getGeom().get();
        const FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        return fact.getOffset(0);
    }

    inline const SpriteAnimationState& SpriteRenderable::getAnimationState() const {
        VertexDataPT &verts = getWindow().getVertices().get<VertexDataPT>();
        Geom &geom = getRenderTask()->getGeom().get();

        return verts.getSpriteAnimationsStates().getItem(geom.getGeomStateId());
    }

    inline Vec2 &SpriteRenderable::accSize() {
        return accRenderTask()->accLocalTransform().accScale();
    }

    inline SpriteAnimationState& SpriteRenderable::accAnimationState() {
        VertexDataPT &verts = getWindow().getVertices().get<VertexDataPT>();
        Geom &geom = getRenderTask()->getGeom().get();
        return verts.getSpriteAnimationsStates().getItem(geom.getGeomStateId());
    }

    inline SpriteRenderable& SpriteRenderable::setAnimated(bool value) {
        Geom &geom = accRenderTask()->getGeom().get();
        if (value)
            geom.setGeomStateType(GeomState::stAnimation);
        else
            geom.setGeomStateType(GeomState::stNone);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setSize(const Vec2 &size) {
        accRenderTask()->accLocalTransform().setScale(size);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setGeomNormOffset(const Vec2 &offset) {
        Geom &geom = getRenderTask()->getGeom().get();
        FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.setOffset(0, offset);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setTextureUnit(u32 tid) {
        PgonTexturedRenderable::setTextureUnit(tid);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setPosition(const Vec2& pos) {
        PgonTexturedRenderable::setPosition(pos);
        return *this;
    }

    inline SpriteRenderable& SpriteRenderable::setImageRegion(const ARect& texture_coords) {
        Geom& geom = getRenderTask()->getGeom().get();
        FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.setTC(0, texture_coords.getLeftTop(), texture_coords.getRightBot());
        return *this;
    }
}