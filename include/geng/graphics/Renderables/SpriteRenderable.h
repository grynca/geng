#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "PgonTexturedRenderable.h"

namespace grynca {

    // fw
    class GeomStateSpriteAnimation;

    class SpriteRenderable : public PgonTexturedRenderable {
    public:
        typedef typename PgonTexturedRenderable::ShaderType ShaderType;
        typedef typename PgonTexturedRenderable::VertexDataType VertexDataType;
        static constexpr GeomUsageHint DefaultUsageHint = GeomUsageHint::uhStatic;

        struct DrawData : public PgonTexturedRenderable::DrawData {
            DrawData() : size(1, 1) {}

            Vec2 size;
        };

        // creates prototype RenderTask for sprite, in order to be later cloned
        static Renderer2D::IPtr createSpritePrototype(const ImagePos& ipos, NormOffset::Type offset_type = NormOffset::otCenter);

        // TODO: enforce dynamic for animated (maybe for animated sprite make own renderable class ?)

        static Geom& createNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint = DefaultUsageHint);

        void setNewGeom(const Vec2& norm_offset, GeomUsageHint usage_hint = DefaultUsageHint);
        void setNewGeom(NormOffset::Type offset_type, GeomUsageHint usage_hint = DefaultUsageHint);

        bool getAnimated()const;
        Vec2 getSize()const;
        Vec2 getGeomNormOffset()const;
        Vec2 getOffset()const;
        const GeomStateSpriteAnimation& getAnimationState()const;

        GeomStateSpriteAnimation& accAnimationState();

        void setAnimated(bool value);
        void setGeomNormOffset(const Vec2& offset);      // normalized to size
        void setImage(const ImagePos& img_pos);
        void setImageRegion(const ARect& texture_coords);
        void setSize(const Vec2& size);

        Vec2& accSize();

        void onBeforeDraw(Shader& s);
    };

}

#include "SpriteRenderable.inl"
#endif //SPRITERENDERABLE_H
