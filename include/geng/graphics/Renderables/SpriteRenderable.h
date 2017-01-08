#ifndef SPRITERENDERABLE_H
#define SPRITERENDERABLE_H

#include "PgonTexturedRenderable.h"

namespace grynca {

    // fw
    class SpriteAnimationState;

    class SpriteRenderable : public PgonTexturedRenderable {
    public:
        typedef typename PgonTexturedRenderable::ShaderType ShaderType;
        typedef typename PgonTexturedRenderable::VertexDataType VertexDataType;

        // creates rect geom (size[1,1], offset[-0.5, -0.5])
        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        SpriteRenderable(const Renderer2D::ItemRef& rt) : PgonTexturedRenderable(rt) {}

        bool getAnimated()const;
        Vec2 getSize()const;
        Vec2 getGeomNormOffset()const;
        const SpriteAnimationState& getAnimationState()const;

        Vec2& accSize();
        SpriteAnimationState& accAnimationState();

        SpriteRenderable& setSize(const Vec2& size);      // changes local transform scale
        SpriteRenderable& setAnimated(bool value);
        SpriteRenderable& setGeomNormOffset(const Vec2& offset);      // normalized to size
        SpriteRenderable& setTextureUnit(u32 tid);
        SpriteRenderable& setPosition(const Vec2& pos);     // changes local transform position
        SpriteRenderable& setImageRegion(const ARect& texture_coords);
    };

}

#include "SpriteRenderable.inl"
#endif //SPRITERENDERABLE_H
