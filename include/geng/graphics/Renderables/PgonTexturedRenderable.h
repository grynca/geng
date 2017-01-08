#ifndef PGONTEXTUREDRENDERABLE_H
#define PGONTEXTUREDRENDERABLE_H

#include "Renderable.h"

namespace grynca {

    // fw
    class SimpleTexturedShader;
    class VertexDataPT;

    class PgonTexturedRenderable : public Renderable {
    public:
        typedef SimpleTexturedShader ShaderType;
        typedef VertexDataPT VertexDataType;

        static VertexData::ItemRef createNewGeom(Window& w, GeomState::UsageHint usage_hint = GeomState::uhStatic);

        PgonTexturedRenderable(const Renderer2D::ItemRef& rt) : Renderable(rt) {}

        PgonTexturedRenderable& setTextureUnit(u32 tid);
        PgonTexturedRenderable& setPosition(const Vec2& pos);       // changes local transform scale
        u32 getTextureUnit()const;
    };

};

#include "PgonTexturedRenderable.inl"
#endif //PGONTEXTUREDRENDERABLE_H
