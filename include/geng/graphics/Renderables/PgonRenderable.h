#ifndef POLYGONRENDERABLE_H
#define POLYGONRENDERABLE_H

#include "Renderable.h"
#include "assets/Image.h"

namespace grynca {

    // fw
    class SimpleColorShader;
    class VertexDataP;

    // Convex polygon
    class PgonRenderable : public Renderable {
    public:
        typedef SimpleColorShader ShaderType;
        typedef VertexDataP VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        PgonRenderable(const Renderer2D::ItemRef& rt) : Renderable(rt) {}

        Colorf getColor()const;
        Colorf& accColor();

        PgonRenderable& setColor(const Colorf& clr);
        PgonRenderable& setPosition(const Vec2& pos);
    };

}

#include "PgonRenderable.inl"
#endif //POLYGONRENDERABLE_H
