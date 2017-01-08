#ifndef RECTBORDERRENDERABLE_H
#define RECTBORDERRENDERABLE_H

#include "RectRenderable.h"

namespace grynca {

    //fw
    class RectBorderShader;

    class RectBorderRenderable : public RectRenderable {
    public:
        typedef RectBorderShader ShaderType;
        typedef typename RectRenderable::VertexDataType VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        RectBorderRenderable(const Renderer2D::ItemRef& rt) : RectRenderable(rt) {}

        Vec2 getBorders()const;
        Vec2 getGeomNormOffset();

        RectBorderRenderable& setColor(const Colorf& clr);
        RectBorderRenderable& setSize(const Vec2& size);        // changes transform scale
        RectBorderRenderable& setGeomNormOffset(const Vec2& offset);
        RectBorderRenderable& setBorders(Vec2 borders_px);
    };
}

#include "RectBorderRenderable.inl"
#endif //RECTBORDERRENDERABLE_H
