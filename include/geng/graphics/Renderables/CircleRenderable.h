#ifndef CIRCLERENDERABLE_H
#define CIRCLERENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class CircleShader;
    class VertexDataP;

    class CircleRenderable : public Renderable {
    public:
        typedef CircleShader ShaderType;
        typedef VertexDataP VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        CircleRenderable(const Renderer2D::ItemRef& rt);

        f32 getInnerRadius()const;
        f32 getOuterRadius()const;
        Colorf getColor()const;
        const Geom& getGeom()const;     // uses shared geom which is read only

        CircleRenderable& setColor(const Colorf& c) ;
        CircleRenderable& setInnerRadius(f32 inner_r);
        CircleRenderable& setOuterRadius(f32 outer_r);
        CircleRenderable& setPosition(const Vec2& pos);
    };
}

#include "CircleRenderable.inl"
#endif //CIRCLERENDERABLE_H
