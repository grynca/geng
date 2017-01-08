#ifndef RECTRENDERABLE_H
#define RECTRENDERABLE_H

#include "PgonRenderable.h"

namespace grynca {

    class RectRenderable : public PgonRenderable {
    public:
        typedef typename PgonRenderable::ShaderType ShaderType;
        typedef typename PgonRenderable::VertexDataType VertexDataType;

        // creates rect geom (size[1,1], offset[-0.5, -0.5])
        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        RectRenderable(const Renderer2D::ItemRef& rt) : PgonRenderable(rt) {}

        Vec2 getSize()const;
        Vec2 getGeomNormOffset()const;

        Vec2& accSize();

        RectRenderable& setColor(const Colorf& clr);
        RectRenderable& setSize(const Vec2& size);      // changes local transform scale
        RectRenderable& setGeomNormOffset(const Vec2& offset);      // normalized to size
    };
}


#include "RectRenderable.inl"
#endif //RECTRENDERABLE_H
