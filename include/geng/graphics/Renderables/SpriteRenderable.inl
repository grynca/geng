#include "SpriteRenderable.h"
#include "../VertexData/Factories/geom_factories.h"
#include "../VertexData/GeomStates/GeomStateSpriteAnimation.h"

namespace grynca {

    inline Renderer2D::IPtr SpriteRenderable::createSpritePrototype(const ImagePos& ipos, NormOffset::Type offset_type) {
        // static
        SpriteRenderable sr = createRenderable<SpriteRenderable>();
        sr.setNewGeom(offset_type);
        sr.setImage(ipos);
        return sr.getRenderTaskPtr();
    }

    inline Geom& SpriteRenderable::createNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint){
        // static
        VertexDataPT& verts = accWindow().getVertices().getFast<VertexDataPT>();
        Geom& geom = verts.addItem(GL_TRIANGLE_FAN, usage_hint);
        FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.add(Vec2{1,1}, norm_offset);
        return geom;
    }

    inline void SpriteRenderable::setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint) {
        setGeom(createNewGeom(norm_offset, usage_hint));
    }

    inline void SpriteRenderable::setNewGeom(NormOffset::Type offset_type, GeomUsageHint usage_hint) {
        setNewGeom(NormOffset::get(offset_type), usage_hint);
    }

    inline bool SpriteRenderable::getAnimated() const {
        const Geom &geom = getRenderTaskPtr()->getGeom().get();
        return geom.getStateType() == gstAnimationSprite;
    }

    inline Vec2 SpriteRenderable::getSize() const {
        return getRenderTaskPtr()->getDrawDataAs<DrawData>().size;
    }

    inline Vec2 SpriteRenderable::getGeomNormOffset() const {
        Geom &geom = const_cast<SpriteRenderable *>(this)->accRenderTaskPtr()->accGeom().acc();
        const FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        return fact.getOffset(0);
    }

    inline Vec2 SpriteRenderable::getOffset()const {
        return getGeomNormOffset()*getSize();
    }

    inline const GeomStateSpriteAnimation& SpriteRenderable::getAnimationState() const {
        const Geom& geom = getRenderTaskPtr()->getGeom().get();
        ASSERT(geom.getStateType() == GeomStateType::gstAnimationSprite);
        return (const GeomStateSpriteAnimation&)(geom.getState());
    }

    inline GeomStateSpriteAnimation& SpriteRenderable::accAnimationState() {
        Geom& geom = accRenderTaskPtr()->accGeom().acc();
        ASSERT(geom.getStateType() == GeomStateType::gstAnimationSprite);
        return (GeomStateSpriteAnimation&)(geom.accState());
    }

    inline void SpriteRenderable::setAnimated(bool value) {
        Geom &geom = accRenderTaskPtr()->accGeom().acc();
        if (value)
            geom.setState(gstAnimationSprite);
        else
            geom.setState(gstNone);
    }

    inline void SpriteRenderable::setGeomNormOffset(const Vec2 &offset) {
        Geom &geom = accRenderTaskPtr()->accGeom().acc();
        FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.setOffset(0, offset);
    }

    inline void SpriteRenderable::setImage(const ImagePos& img_pos) {
        PgonTexturedRenderable::setTextureUnit(img_pos.getTextureId());
        setImageRegion(img_pos.getTextureRegion()->getTextureRect());
    }

    inline void SpriteRenderable::setImageRegion(const ARect& texture_coords) {
        Geom& geom = accRenderTaskPtr()->accGeom().acc();
        FactoryRectTF<VertexDataPT::Vertex> fact = geom.getFactory<FactoryRectTF<VertexDataPT::Vertex> >();
        fact.setTC(0, texture_coords.getLeftTop(), texture_coords.getRightBot());
    }

    inline void SpriteRenderable::setSize(const Vec2& size) {
        accRenderTaskPtr()->accDrawDataAs<DrawData>().size = size;
    }

    inline Vec2& SpriteRenderable::accSize() {
        return accRenderTaskPtr()->accDrawDataAs<DrawData>().size;
    }

    inline void SpriteRenderable::onBeforeDraw(Shader& s) {
        DrawData& dd = accRenderTaskPtr()->accDrawDataAs<DrawData>();
        dd.transform *= Mat3::createScaleT(dd.size);

        SimpleTexturedShader& sts = (SimpleTexturedShader&)s;
        sts.setUniforms(dd);
    }
}